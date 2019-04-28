$(document).ready(function(){	
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	var my_email = localStorage.getItem("my_id");
	var room_id = localStorage.getItem("room_id");

	//방 아이디 받아오기
	socket.emit('room_id', room_id);
	socket.on('room_id', function(data){
		socket.emit('pre_msg', room_id);
	});

	//이전 메세지 목록 받아오기
	socket.on('pre_msg', function(data){
		var i;
		for (i=0; i<data.length; i++){
			$('#chat_list').append('<p>'+data[i].user+' : '+data[i].msg+'</p>');
		}
	});

	//메세지 보내기
	$('#msg').click(function(){
		var msg = $('#msgbox').val();
		socket.emit('msg', [room_id, my_email, msg]);
		$('#msgbox').val('');
	});

	//새 메세지 받기	
	socket.on('new_chat', function(data){
		$('#chat_list').append('<p>'+data[0]+' : '+data[1]+'</p>');
	});
});