var g_lat, g_lon;

$(document).ready(function(){
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	var my_email = localStorage.getItem("my_id");
	var my_name = localStorage.getItem("my_name");

	//패널 오픈
	$('#aboutme').click(function(){
		var str = "<h1>";
		str += my_name;
		str += "</h1>";

		var signout = '<a href="signin.html" rel="external" class="ui-btn">로그아웃</a>';
		$('#mypanel').html(str + signout);
	});

	//현재 날짜/시간 설정
	var date = new Date();
	var day = date.getDay(); 	//일요일(0)
	var hour = date.getHours();
	//var minute = date.getMinutes();
	var day_string;
	switch (day){
		case 0:
			day_string = 'sun';
			break;
		case 1:
			day_string = 'mon';
			break;
		case 2:
			day_string = 'tue';
			break;
		case 3:
			day_string = 'wed';
			break;
		case 4:
			day_string = 'thu';
			break;
		case 5:
			day_string = 'fli';
			break;
		case 6:
			day_string = 'sat';
			break;
	}

	//day_string = 'mon';

	if (day_string=='sun' || day_string=='sat'){
		$('#free_list').html('<h1 style="text-align:center;">오늘은 주말입니다!</h1>')
	}

	var timetable = [], cnt=0;

	socket.emit('free_list', my_email);
	socket.emit('sort_print_list', '');

	socket.on('free_list', function(list){
		timetable[cnt] = list;
		cnt++;
	});

	socket.on('sort_print_list', function(data){

		//0, 1~12교시 까지 시작 시간
		var table = [8 ,9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20];
		var t, i, j, temp;

		//hour = 10;

		for (t=0; t<timetable.length; t++){
			for (i=0; i<timetable[t].length; i++){
				for (j=i; j<timetable[t].length; j++){
					if (timetable[t][i].day > timetable[t][j].day){
						temp = timetable[t][i];
						timetable[t][i] = timetable[t][j];
						timetable[t][j] = temp;
					}
				}
			}
		}

		var new_chk = '';
		for (t=0; t<timetable.length; t++){
			for (i=0; i<timetable[t].length; i++){
				//mon1 -> mon 1 분리
				var today = timetable[t][i].day.substring(0,3);
				var time = parseInt(timetable[t][i].day.substring(3,5));
				if (today != day_string) continue;
				else if (hour >= table[time]) continue;

				if (new_chk != timetable[t][i].user) new_chk = timetable[t][i].user;
				else break;

				timetable[t][0] = timetable[t][i];
			}
		}

		for (i=0; i<timetable.length; i++){
			for (j=i; j<timetable.length; j++){
				var time_i = parseInt(timetable[i][0].day.substring(3,5));
				var time_j = parseInt(timetable[j][0].day.substring(3,5));
				if (time_i > time_j){
					temp = timetable[i];
					timetable[i] = timetable[j];
					timetable[j] = temp;
				}
			}
		}
		for (t=0; t<timetable.length; t++){		
			if (timetable[t][0].day.substring(0,3) != day_string) continue;	
			var time = parseInt(timetable[t][0].day.substring(3,5));
			socket.emit('friend_name', timetable[t][0].user);
			$('#free_list').append('<div class="friend ui-btn" id="'+timetable[t][0].user+'">&nbsp;<span class="user">'+ timetable[t][0].name+'</span>---<span class="time">'+table[time]+':00 강의</span></div>');
		}
	});

	$(document).on('click', '.friend', function(){
		var friend_id = $(this).attr('id');
		var friend_name = $(this).text();
		socket.emit('get_geolocation', friend_id);
		socket.on('get_geolocation', function(data){
			g_lat = data.lat;
			g_lon = data.lon;
			var name = '<p class="title">'+ friend_name +'</p>';
			/*
			var map = '<iframe width="100%" height="350" frameborder="0" style="border:0"';
			map +=  'src="https://www.google.com/maps/embed/v1/place?key=AIzaSyCn36EE4Q_0ylC7fAVJqZagZA0LM_oo_dU';
			map += '&q=대한민국&center=';
			map += data.lat;
			map += ',';
			map += data.lon;
			map += '&zoom=17" allowfullscreen></iframe>';
			*/
			var map = '<div id="map"  style="width:100%;height: 350px;"></div>';
			getLocation();

			var call = '<a class="ui-btn" href="tel:'+data.call+'">'+data.call+'</a>';
			$('#detail').html(name + map + call);
			$('#detail').bPopup({
				follow: [false, false],
				position: [5, 100]
			});
		});
	});
});

function mapView(lat,lan) {
   	var latlngDC = new google.maps.LatLng( g_lat, g_lon);   
   	var mapOptions = { zoom: 16, center: latlngDC  };
    
   	map = new google.maps.Map( document.getElementById('map'), mapOptions );
 
   	var marker = new google.maps.Marker( { 
       	position: latlngDC,     
       	map: map,      
       	title: "표시" 
   	});
}

function getLocation() {
    if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showPosition, showError);
    } else {
      	$("#map").text("지도지원안함");
    }
}
function showPosition(position) {
	lat = position.coords.latitude ;
	lan = position.coords.longitude;
	mapView(lat,lan);
}
function showError(error) {
   	("#map").text("지도 가져오기 오류");
}
