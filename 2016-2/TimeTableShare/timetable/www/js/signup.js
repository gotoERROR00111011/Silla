$(document).ready(function(){
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	$('#signup').click(function(){
		var email = $('#email').val();
		var pw = $('#pw').val();
		var name = $('#name').val();
		var call = $('#call').val();
		var data = [email, pw, name, call];
		socket.emit('signup', data);	
		socket.on('find', function(data){
			alert('이미 등록된 이메일 입니다.');
		});
		socket.on('signup_ok', function(data){
			location.replace('signin.html');
		});
	});
});
