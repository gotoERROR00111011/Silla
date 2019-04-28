<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
<%
 String t_code =(String)session.getAttribute("t_code");
 String level =(String)session.getAttribute("level");
/* out.print(t_code); */

%>
<!DOCTYPE html>
<html lang="ko">
<head>
  <title>SMART PORT</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
  <style type="text/css">
    body{
      background: url(img/main_img.png) no-repeat center center fixed; 
      -webkit-background-size: cover;
      -moz-background-size: cover;
      -o-background-size: cover;
      background-size: cover;
    }
    @font-face{
      font-family:'PublicBath1';
      src:url('font/PublicBath1.ttf') format("truetype");
    }
    .terminal_bt{
      height: 80px;
      width: 80px;
      background-color: rgb(57,124,188);
      font-family:PublicBath1;
      font-size:20;
    }
    #terminal_list{
      margin-top: 30px;
    }
    .navbar{
      background-color: rgba(255,255,255.0.5);
      margin: 10px;
      bottom: 5px;
      font-family:PublicBath1;
    }
    .navbar-text{
      font-style: italic;
      color:red; 
      font-size:30px

    }
    .footer {
     position: fixed;
     left: 0;
     bottom: 0;
     width: 100%;
     color: white;
     text-align: center;

   }
   .footer_bt{
      height: 60px;
      margin-bottom: 20px;
      margin-left: : 10px;
      background-color: rgba(0,0,0,0.5);
   }
 
  </style>
  <script type="text/javascript">
  $(document).ready(function() {
	
	$("#logout_icon").click(function() {
        location.href="logout.jsp"
    });
    $(".terminal_bt").click(function() {
        var t_code = $(this).text();
        sessionStorage.setItem("t_code", t_code);
        location.href="sub_lo.jsp?t_code="+t_code;
        /* location.href="NewFile.jsp?t_code="+t_code; */
    });
    
    $(".footer_bt").click(function() {
        var b_value = $(this).val();
        if(b_value == "qrcode"){
          location.href="qrcode_scan.jsp";
        }else{
          location.href="http://web.kma.go.kr/aboutkma/intro/busan/local/port3/index.jsp";
        }
    });
  });
</script>
</head>

<body>
  <header>
 
    <nav class="navbar">
      <div class="col-xs-10">
        <h1 class="navbar-text" >SMART PORT</h1>
        <!-- <a class="navbar-brand" href="#">SMART PORT</a> -->
      </div>
      <div class="col-xs-2">
        <ul class="nav navbar-nav navbar-right" >
          <%
 	String id = (String)session.getAttribute("id");
 	if(id == null)
 	{	
	 %>
          <a href="login.jsp"><li id="login_icon"><span class="glyphicon glyphicon-user"  aria-hidden="true"></span></li></a>
     <% }  
     
     else
 	{	
	 %>
           <a href="logout.jsp"><li id="logout_icon">로그아웃</li></a>
     <% } %> 
          
        </ul>
      </div>
    </nav>
  </header>
  <div class="container">
    <div class="row">
      <div class="col-xs-1"> 왼쪽 </div>
      <div class="col-xs-10">
        <div id="terminal_list">
          <div class="row">
            <div class="col-xs-4">
              <button type="button" class="btn btn-primary btn-md terminal_bt" name="terminal_code" value="PECTC">PECTC</button>
            </div>
            <div class="col-xs-4">
              <button type="button" class="btn btn-primary btn-md terminal_bt" name="terminal_code" value="DPCTC">DPCTC</button>
            </div>
            <div class="col-xs-4">
              <button type="button" class="btn btn-primary btn-md terminal_bt" name="terminal_code" value="BNCTC">BNCTC</button>
            </div>
          </div>  
          <div class="row" style="height: 20px;"></div>
          <div class="row">
            <div class="col-xs-4">
              <button type="button" class="btn btn-primary btn-md terminal_bt" name="terminal_code" value="PNDKC">PNDKC</button>
            </div>
            <div class="col-xs-4">
              <button type="button" class="btn btn-primary btn-md terminal_bt" name="terminal_code" value="BCTOC">BCTOC</button>
            </div>
            <div class="col-xs-4">
              <button type="button" class="btn btn-primary btn-md terminal_bt" name="terminal_code" value="HJNPC">HJNPC</button>
            </div>
          </div> 
        </div>
      </div>
      <div class="col-xs-1"> 오른쪽 </div>
    </div>
    
  </div>
  <div class="footer">
    <div class="container">
      <div class="row">
        <div class="col-xs-6" style="padding: 2px;">
          <button type="button" class="btn footer_bt" style="width:166.78px" value="weather" >부산항 항만 기상정보</button>
        </div>
        <div class="col-xs-6" style="padding: 2px; ">
          <button type="button" class="btn footer_bt" value="qrcode">컨테이너 QR코드 스캔</button>
        </div>
      </div>
    </div>
  </div>
</body>

</html>
