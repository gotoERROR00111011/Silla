$(document).ready(function(){
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	var my_email = localStorage.getItem("my_id");
	var my_name = localStorage.getItem("my_name");
	var this_lec = '';

	socket.emit('timetable', my_email);

	//시간표 로드
	socket.on('timetable', function(list){		
		var i = 0;
		for (i=0; i<list.length; i++){
			$('#'+list[i].day).css('background-color','black');
			$('#'+list[i].day).css('color','white');
			$('#'+list[i].day).html('<p class="br">' +list[i].lec + '</p><p class="br">' + list[i].room + '</p><p class="br">' + list[i].prof + '</p>');
		}
	});
	
	//시간표 입력
	$(document).on('click', '.lecture', function(){
		var lecture = $(this).attr('id');
		this_lec = lecture;
		$('#addLecture').bPopup({
			follow: [false, false],
			position: [5, 100]
		});
	});

	//시간표 삭제
	$('#del').click(function(){
		var lec_time = this_lec;
		data = [lec_time, my_email];
		socket.emit('del_lecture', data);
		$('#addLecture').bPopup().close();
		alert('삭제완료!');
		window.location.reload();
	});

	//시간표 제출
	$('#add').click(function(){
		var lec_time = this_lec;
		var lec_name = $('#lecture_name').val();
		var lec_room = $('#lecture_room').val();
		var prof = $('#professor').val();
		var data = [lec_time, lec_name, lec_room, prof, my_email, my_name];
		socket.emit('add_lecture', data);
		$('#addLecture').bPopup().close();
		alert('추가완료!');
		window.location.reload();
	});
});