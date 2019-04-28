$(document).ready(function(){
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	var my_email = localStorage.getItem("my_id");
	var my_name = localStorage.getItem("my_name");

	socket.emit('room_list', my_email);
	//방 목록 보여주기
	socket.on('room_list', function(list){
		var i = 0;
		for (i=0; i<list.length; i++){
			$('#room_list').append('<div class="ui-btn open_room" data-inset="true" id="'+list[i]._id+'">'+list[i].name+'</div>');
		}
	});

	//방 들어가기
	//동적으로 생성된 태그 이벤트
	$(document).on('click', '.open_room', function(){
		var room_id = $(this).attr('id');
		socket.emit('open_room', room_id);
		socket.on('open_room', function(data){	
			localStorage.setItem("room_id", room_id);
			location.replace('chat_room.html');
		});		
	});
	
	//방 초대 목록
	$('#roommate').click(function(){
		socket.emit('friend_list', my_email);
		socket.on('friend_list', function(list){
			$('.addFriend').remove();
			var i = 0;
			for (i=0; i<list.length; i++){
				$('#popupCreateRoom').append('<label class="addFriend"><input type="checkbox" name="friend" id="'+list[i].friend_name+'" value="'+list[i].friend+'">'+list[i].friend_name+"</label>");
			}
		});
	});

	//방 만들기
	$('#createRoom').click(function(){
		var email = [my_email];
		var name = [my_name];
		var cnt = 1;
		$('input:checkbox[name="friend"]').each(function() {
     		if(this.checked == true){ 
            	email[cnt] = this.value;
            	name[cnt] = $(this).attr('id');
            	cnt++;
      		}
 		});
 		var member = [];
 		member[0] = email;
 		member[1] = name;
		socket.emit('create_room', member);	
		socket.on('create_room_result', function(data){
			window.location.reload();
		});
	});	
});
