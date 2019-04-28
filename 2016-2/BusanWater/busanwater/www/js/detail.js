$(document).ready(function(){
	var get = location.href.split("?");
	var code = get[1].split("&");
	var temp = [code[0].split("="), code[1].split("="), code[2].split("="), code[3].split("=")];
	var point = temp[0][1];
	var gu = temp[1][1];
	var year = temp[2][1];
	var water = temp[3][1];

	$("#point").text(decodeURI(point));
	
	var back_gu = localStorage.getItem("gu");
	var back_year = localStorage.getItem("year");
	
	$("#back").attr("href", "water.html?gu="+back_gu+"&year="+back_year+"&water="+water);
	
    var url = "http://opendata.busan.go.kr/openapi/service/DrinkableWaterQualityInfoService/getDrinkableWaterQualityInfo";
    url += "?serviceKey=XHBhuxDgBfW6v%2FHx5t%2BdOLmBEFwTTYiwhKXtAdL2j%2B%2BtDMJrrLhjwwdbToX8mdv3DYCxF611DP9xy4ZVu5YmuA%3D%3D";
    url += "&gu=" + gu;
    url += "&point=" + point;
    url += "&yy=" + year;

    $.ajax({
    	type: "GET",             
		url: url,
  		//data: "{}",
 		cache: false,
  		dataType: "xml",
  		success: onSuccess
    });
	
	function onSuccess(data){ 
		$(data).find("item").each(function(){
			var color = "black";
			var str = "<li data-role='list-divider'>";
			str += $(this).find("inspecArea").text() + " ";
			str += $(this).find("inspecPoint").text() + " ";
			str += $(this).find("result").text() + " ";
			str += $(this).find("inspecYy").text() + "년";
			str += "</li>";
				
			var chk;
			
			chk= $(this).find("water01").text();
			if (chk == "불검출" || chk<0.5) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>암모니아성질소(0.5mg/L) : " + $(this).find("water01").text() + "</span></li>";

			chk= $(this).find("water02").text();
			if (chk == "불검출" || chk<10) color = "blue";
			else color = "red";		
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>질산성질소(10mg/L) : " + $(this).find("water02").text() + "</span></li>";

			chk= $(this).find("water03").text();
			if (chk == "불검출" || chk<10) color = "blue";
			else color = "red";	
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>과망간산칼륨소비량(10mg/L) : " + $(this).find("water03").text() + "</span></li>";

			chk= $(this).find("water04").text();
			if (chk == "불검출" || chk<500) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>증발잔류물 : " + $(this).find("water04").text() + "</span></li>";

			chk= $(this).find("water05").text();
			if (chk == "불검출" || chk<100) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>일반세균(100CFU/mL) : " + $(this).find("water05").text() + "</span></li>";

			chk= $(this).find("water06").text();
			if (chk == "불검출" || chk<100) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>총대장균군(불검출/100mL) : " + $(this).find("water06").text() + "</span></li>";
			
			chk= $(this).find("water07").text();
			if (chk == "불검출" || chk<100) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>분원성대장균군(불검출/100mL) : " + $(this).find("water07").text() + "</span></li>";

			chk= $(this).find("water08").text();
			if (chk == "불검출" || chk<2) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>여시니아균(불검출/2L) : " + $(this).find("water08").text() + "</span></li>";

			chk= $(this).find("water09").text();
			if (chk == "불검출" || chk<0.01) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>납(0.01mg/L) : " + $(this).find("water09").text() + "</span></li>";

			chk= $(this).find("water10").text();
			if (chk == "불검출" || chk<1.5) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>불소(1.5mg/L) : " + $(this).find("water10").text() + "</span></li>";

			chk= $(this).find("water11").text();
			if (chk == "불검출" || chk<0.01) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>비소(0.01mg/L) : " + $(this).find("water11").text() + "</span></li>";

			chk= $(this).find("water12").text();
			if (chk == "불검출" || chk<0.01) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>세레늄(0.01mg/L) : " + $(this).find("water12").text() + "</span></li>";

			chk= $(this).find("water13").text();
			if (chk == "불검출" || chk<0.001) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>수은(0.001mg/L) : " + $(this).find("water13").text() + "</span></li>";

			chk= $(this).find("water14").text();
			if (chk == "불검출" || chk<0.01) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>시안(0.01mg/L) : " + $(this).find("water14").text() + "</span></li>";

			chk= $(this).find("water15").text();
			if (chk == "불검출" || chk<0.05) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>6가크롬(0.05mg) : " + $(this).find("water15").text() + "</span></li>";

			chk= $(this).find("water16").text();
			if (chk == "불검출" || chk<0.005) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>카드뮴(0.005mg/L) : " + $(this).find("water16").text() + "</span></li>";

			chk= $(this).find("water17").text();
			if (chk == "불검출" || chk<1.0) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>보론(1.0mg/L) : " + $(this).find("water17").text() + "</span></li>";

			chk= $(this).find("water18").text();
			if (chk == "불검출" || chk<0.005) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>페놀(0.005mg/L) : " + $(this).find("water18").text() + "</span></li>";

			chk= $(this).find("water19").text();
			if (chk == "불검출" || chk<0.02) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>다이아지논(0.02mg/L) : " + $(this).find("water19").text() + "</span></li>";

			chk= $(this).find("water20").text();
			if (chk == "불검출" || chk<0.06) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>파라티온(0.06mg/L) : " + $(this).find("water20").text() + "</span></li>";

			chk= $(this).find("water21").text();
			if (chk == "불검출" || chk<0.04) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>페니트로티온(0.04mg/L) : " + $(this).find("water21").text() + "</span></li>";

			chk= $(this).find("water22").text();
			if (chk == "불검출" || chk<0.07) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>카바릴(0.07mg/L) : " + $(this).find("water22").text() + "</span></li>";

			chk= $(this).find("water23").text();
			if (chk == "불검출" || chk<0.1) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>1.1.1-트리클로로에탄(0.1mg/L) : " + $(this).find("water23").text() + "</span></li>";

			chk= $(this).find("water24").text();
			if (chk == "불검출" || chk<0.01) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>테트라클로로에틸렌(0.01mg/L) : " + $(this).find("water24").text() + "</span></li>";

			chk= $(this).find("water25").text();
			if (chk == "불검출" || chk<0.03) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>트리클로로에틸렌(0.03mg/L) : " + $(this).find("water25").text() + "</span></li>";
			
			chk= $(this).find("water26").text();
			if (chk == "불검출" || chk<0.02) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>디클로로메탄(0.02mg/L) : " + $(this).find("water26").text() + "</span></li>";

			chk= $(this).find("water27").text();
			if (chk == "불검출" || chk<0.01) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>벤젠(0.01mg/L) : " + $(this).find("water27").text() + "</span></li>";

			chk= $(this).find("water28").text();
			if (chk == "불검출" || chk<0.7) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>톨루엔(0.7mg/L) : " + $(this).find("water28").text() + "</span></li>";

			chk= $(this).find("water29").text();
			if (chk == "불검출" || chk<0.3) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>에틸벤젠(0.3mg/L) : " + $(this).find("water29").text() + "</span></li>";

			chk= $(this).find("water30").text();
			if (chk == "불검출" || chk<0.5) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>크실렌(0.5mg/L) : " + $(this).find("water30").text() + "</span></li>";

			chk= $(this).find("water31").text();
			if (chk == "불검출" || chk<0.03) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>1.1-디클로로에틸렌(0.03mg/L) : " + $(this).find("water31").text() + "</span></li>";

			chk= $(this).find("water32").text();
			if (chk == "불검출" || chk<0.002) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>사염화탄소(0.002mg/L) : " + $(this).find("water32").text() + "</span></li>";

			chk= $(this).find("water33").text();
			if (chk == "불검출" || chk<0.003) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>1.2-디브로모-3-클로로프로판(0.003mg/L) : " + $(this).find("water33").text() + "</span></li>";

			chk= $(this).find("water34").text();
			if (chk == "불검출" || chk<1000) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>경도(1000mg/L) : " + $(this).find("water34").text() + "</span></li>";

//----------------------------냄새 맛 재검토
			chk= $(this).find("water35").text();
			if (chk == "없음") color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>냄새 : " + $(this).find("water35").text() + "</span></li>";

			chk= $(this).find("water36").text();
			if (chk == "없음") color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>맛 : " + $(this).find("water36").text() + "</span></li>";
//--------------------------------------------
			chk= $(this).find("water37").text();
			if (chk == "불검출" || chk<1) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>동(1mg/L) : " + $(this).find("water37").text() + "</span></li>";

			chk= $(this).find("water38").text();
			if (chk == "불검출" || chk<5) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>색도(5도이하) : " + $(this).find("water38").text() + "</span></li>";

			chk= $(this).find("water39").text();
			if (chk == "불검출" || chk<0.5) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>세제(0.5mg/L) : " + $(this).find("water39").text() + "</span></li>";

			chk= $(this).find("water40").text();
			if (chk == "불검출" || (chk>=5.8&&chk<=8.5)) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>수소이온농도(5.8~8.5) : " + $(this).find("water40").text() + "</span></li>";

			chk= $(this).find("water41").text();
			if (chk == "불검출" || chk<3) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>아연(3mg/L) : " + $(this).find("water41").text() + "</span></li>";

			chk= $(this).find("water42").text();
			if (chk == "불검출" || chk<250) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>염소이온(250mg/L) : " + $(this).find("water42").text() + "</span></li>";

			chk= $(this).find("water43").text();
			if (chk == "불검출" || chk<0.3) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>철(0.3mg/L) : " + $(this).find("water43").text() + "</span></li>";

			chk= $(this).find("water44").text();
			if (chk == "불검출" || chk<0.3) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>망간(0.3mg/L) : " + $(this).find("water44").text() + "</span></li>";

			chk= $(this).find("water45").text();
			if (chk == "불검출" || chk<1.0) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>탁도(1NTU이하) : " + $(this).find("water45").text() + "</span></li>";

			chk= $(this).find("water46").text();
			if (chk == "불검출" || chk<250) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>황산이온(250mg/L) : " + $(this).find("water46").text() + "</span></li>";

			chk= $(this).find("water47").text();
			if (chk == "불검출" || chk<0.2) color = "blue";
			else color = "red";
			if (!(chk == "-" || chk == "")) 
				str += "<li><span style='color:"+color+";'>알루미늄(0.2mg/L) : " + $(this).find("water47").text() + "</span></li>";			
			
			$("#listv").append(str);
			$("#listv").listview('refresh');			
		});
	}
});