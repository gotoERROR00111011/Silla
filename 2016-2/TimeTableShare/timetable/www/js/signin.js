$(document).ready(function(){
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	$('#signin').click(function(){
		var email = $('#email').val();
		var pw = $('#pw').val();
		var data = [email, pw];
		socket.emit('signin', data);
		socket.on('signin_ok', function(data){
			localStorage.setItem("my_id", email);
			localStorage.setItem("my_name", data);
			location.replace('free_list.html');	
		});
		socket.on('signin_no', function(data){
			alert('일치하는 아이디/비밀번호 가 없습니다.');
		});
	});
});
