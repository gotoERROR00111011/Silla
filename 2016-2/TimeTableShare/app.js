//필요한 기능 추가
var socketio = require('socket.io');
var express = require('express');
var http = require('http');
var mongoose = require('mongoose');

//몽고DB 연결
mongoose.connect('mongodb://localhost/timetable');
var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback(){
	console.log("mongoDB open");
})

//서버 설정
var app = express();
app.set('port', 8080);
var server = http.createServer(app).listen(app.get('port'), function(){
	console.log("express server listening on port " + app.get('port'));
});

		//console.log(data[0]);

//서버 대기
var io = socketio.listen(server);

//socket 연결
io.sockets.on('connection', function(socket){ console.log("socket connect");
	//회원가입 기능
	socket.on('signup', function(data){
		var email = data[0];
		var pw = data[1];
		var name = data[2];
		var call = data[3];
		db.collection('user').findOne({_id:email}, function(err, docs){
			if(err) {
				throw err;
			} else if(docs == null){
				db.collection('user').save({_id:email,pw:pw,name:name,lat:35.1681655, lon:128.9936828, call:call}, function(err, docs){
					if(err) throw err;
					socket.emit('signup_ok', '');
				});
			} else {
				socket.emit('find', 'f');
			}
		});
	});
	//로그인 기능
	socket.on('signin', function(data){
		console.log("실행됨");
		console.log(data[0]);
		db.collection('user').findOne({_id:data[0],pw:data[1]}, function(err, docs){
			if(err) {
				throw err;
			} else if (docs == null){
				socket.emit('signin_no', '');
			} else {
				socket.emit('signin_ok', docs.name);
			}
		});
	});

	//친구 목록 기능
	socket.on('friend_list', function(data){
		db.collection('friend').find({me:data}).toArray(function(err, docs){
			if(err) { 
				throw err;
			} else {
				socket.emit('friend_list', docs);
			}
		});
	});

	//친구 추가 기능
	socket.on('friend_add', function(data){
		db.collection('user').findOne({_id:data[1]}, function(err, docs){
			if(err){
				throw err;
			} else if (docs == null) {
				socket.emit('friend_add_result', 'no');
			} else {
				db.collection('friend').findOne({me:data[0], friend:data[1]}, function(err, check){
					if(err){
						throw err;
					} else if (check == null){
						db.collection('friend').insert({me:data[0], friend:data[1], friend_name:docs.name});
						socket.emit('friend_add_result', 'yes');
					}
				});
			}
		});
	});
	//방 목록 보여주기 
	socket.on('room_list', function(data){
		db.collection('room').find({user:data}).toArray(function(err, docs){
			if(err){
				throw err;
			} else {
				socket.emit('room_list', docs);
			}
		});
	});
	//방만들기
	socket.on('create_room', function(data){
		db.collection('room').insert({user:data[0], name:data[1]});
		socket.emit('create_room_result', '');
	});
	//방 들어가기
	socket.on('open_room', function(data){
		socket.emit('open_room', data);
	});
	//현재 방 정보
	socket.on('room_id', function(data){
		socket.emit('room_id', data);
		socket.join(data);
	});
	//이전 메세지 목록 보내기
	socket.on('pre_msg', function(data){
		db.collection('chat').find({room_id:data}).toArray(function(err, docs){
			if (err){
				throw err;
			} else {
				socket.emit('pre_msg', docs);
			}
		});
	});
	//메세지 입력
	socket.on('msg', function(data){
		db.collection('chat').insert({
			room_id:data[0],
			user:data[1],
			msg:data[2],
			date:new Date()
		});
		var msg = [data[1], data[2]];
		io.sockets.in(data[0]).emit('new_chat',msg);
	});

	//시간표 추가
	socket.on('add_lecture', function(data){
		db.collection('lecture').insert({
			day:data[0],
			lec:data[1],
			room:data[2],
			prof:data[3],
			user:data[4],
			name:data[5]
		});
	});

	//시간표 삭제
	socket.on('del_lecture', function(data){
			db.collection('lecture').remove({
			day:data[0],
			user:data[1]
		});
	});

	//시간표 목록 보내기
	socket.on('timetable', function(data){
		db.collection('lecture').find({user:data}).toArray(function(err, docs){
			if (err){
				throw err;
			} else {
				socket.emit('timetable', docs);			
			}
		});
	});

	//공강 목록 보내기
	socket.on('free_list', function(data){
		db.collection('friend').find({me:data}).toArray(function(err, docs){
			if (err){
				throw err;
			} else {
				var i;
				if (docs != null){
					for (i=0; i<docs.length; i++){
						db.collection('lecture').find({user:docs[i].friend}).toArray(function(err, list){
							if (err){
								throw err;
							} else {
								socket.emit('free_list', list);
							}
						});
					}
				}
			}
		});
	});
	socket.on('sort_print_list', function(data){
		socket.emit('sort_print_list', '');
	});
	//지도 위치 받기
	socket.on('geolocation', function(data){
		db.collection('user').update({_id:data[2]}, {$set:{lat:data[0], lon:data[1]}});
	});
	//지도 위치 보내기
	socket.on('get_geolocation', function(data){
		db.collection('user').findOne({_id:data}, function(err, docs){
			if (err){
				throw err;
			} else {
				socket.emit('get_geolocation', docs);
			}
		});
	});
});