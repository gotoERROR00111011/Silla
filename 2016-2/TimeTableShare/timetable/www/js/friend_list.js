var g_lat, g_lon;

$(document).ready(function(){
	var serverIP = 'http://172.17.19.149:8080';
	var socket = io.connect(serverIP);
	var my_email = localStorage.getItem("my_id");

	socket.emit('friend_list', my_email);

	//친구목록
	socket.on('friend_list', function(list){
		if (list != null){
			var i = 0;
			for (i=0; i<list.length; i++){
				$('#friend_list').append('<div class="friend ui-btn" data-inset="true" id="'+list[i].friend+'">'+list[i].friend_name+'</div>');
			}
		}	
	});

	//친구추가
	$('#friend_add').click(function(){
		var friend = $('#friend_email').val();
		socket.emit('friend_add', [my_email, friend]);
	});

	//친구추가 실패
	socket.on('friend_add_result', function(result){
		if (result == 'yes') alert('친구 추가 성공!');
		else if (result =='no') alert('일치하는 사용자가 없습니다.');		
		window.location.reload();
	});

	$(document).on('click', '.friend', function(){
		var friend_id = $(this).attr('id');
		var friend_name = $(this).text();
		socket.emit('get_geolocation', friend_id);
		socket.on('get_geolocation', function(data){
			g_lat = data.lat;
			g_lon = data.lon;
			/*
			var name = '<p class="title">'+ friend_name +'</p>';
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
