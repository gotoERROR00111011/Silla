$(document).ready(function(){
	var get = location.href.split("?");
	var code = get[1].split("&");
	var temp = [code[0].split("="), code[1].split("="), code[2].split("=") ];
	var gu = temp[0][1];
	var year = temp[1][1];
	var water = temp[2][1]; //0:전체, 1:적합, 2:부적합
	$("#gu").text(decodeURI(gu) + " " + year);
	
    var url = "http://opendata.busan.go.kr/openapi/service/DrinkableWaterQualityInfoService/getDrinkableWaterQualityInfo";
    url += "?serviceKey=XHBhuxDgBfW6v%2FHx5t%2BdOLmBEFwTTYiwhKXtAdL2j%2B%2BtDMJrrLhjwwdbToX8mdv3DYCxF611DP9xy4ZVu5YmuA%3D%3D";
    url += "&gu=" + gu;
    url += "&yy=" + year;
    url += "&numOfRows=" + 1000;
        
    $.ajax({
    	type: "GET",             
		url: url,
  		//data: "{}",
 		cache: false,
  		dataType: "xml",
  		success: onSuccess
    });
	
	function onSuccess(data){ 
		var cnt = 0;
		$(data).find("item").each(function(){
			if ((water==0)||(water==1&&$(this).find("result").text()=="적합")||(water==2&&$(this).find("result").text()=="부적합")){
				cnt++;
				var str = "<li>";
				str += "<a href='detail.html?gu="+$(this).find("inspecPoint").text()+"&area="+$(this).find("inspecArea").text()+"&year="+$(this).find("inspecYy").text()+"&water="+water+"' rel='external'>";
				str += $(this).find("inspecPoint").text();
				str += " ";
				if ($(this).find("result").text() == "부적합")
					str += "<span style='color:red;'>";
				else
					str += "<span style='color:blue;'>";
				str += $(this).find("result").text();		
				str += "</span>";
				//str += " " + $(this).find("inspecYy").text();
				str += "</a>";
				str += "</li>";
				$("#listv").append(str);
				$("#listv").listview('refresh');	
			}
		});
		if (cnt == 0){
			var str = "<li>";
			str += "<a href='index.html' rel='external'>";
			str += "해당 년도의 자료가 없습니다.";
			str += "</a>";
			str += "</li>";
			$("#listv").append(str);
			$("#listv").listview('refresh');				
		}
	}
});