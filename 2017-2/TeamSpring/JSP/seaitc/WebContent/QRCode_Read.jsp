 <%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page import="seaitc.*" %>
<%@ page import = "java.io.PrintWriter" %>
<%@ page import="java.util.*"%>
<%@ page import="java.text.SimpleDateFormat"%> 
<!DOCTYPE html>
<%
	notice_qr notice_qr = new notice_qr();
	DAO dao = new DAO();
	notice_qr = dao.notice_qr_now();
	String notice_qr_weight ="";
	notice_qr_weight = dao.notice_qr_now_container_weight(notice_qr.getContainer_code());
	String notice_qr_weight_now ="";
	notice_qr_weight_now = dao.notice_qr_now_weight(notice_qr.getContainer_code());
%>
<html>
    <head class="white">
        <!-- jQuery -->
        <script src="http://code.jquery.com/jquery-2.0.1.min.js"></script>
        <!-- Compiled and minified CSS -->
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.2/css/materialize.min.css">
        <!-- Compiled and minified JavaScript -->
        <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.2/js/materialize.min.js"></script>
        <!-- icon -->
        <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
        <link type="text/css" rel="stylesheet" href="css/materialize.min.css"  media="screen,projection"/>
        <meta name="viewport" content="initial-scale=1.0, user-scalable=no">
    </head>
   	<style type="text/css">
    table{
        border: 1px solid grey;
        text-align: center;
        width: 90%;
      }
      tr td{
        text-align: center;
        border: 1px solid grey;
        height: 40px;
      }
      th{
        text-align: center;
        border: 1px solid grey;
        background-color: #EAEAEA;
      }
      </style>

    <body class="white fontStyle">
        <div class="row" style="margin-top: 50px;">
            <div class="container" style="margin-top:15px;">
    <div class="row" id="images">
    </div>
    <div class="row">

	        
	 <div class="center-align"><h1><%=notice_qr.getContainer_code() %> </h1></div>
      <table align="center">
	        <tr>
	          <th>터미널</th>
	          <td id="t_code"><%=notice_qr.getTerminal_code() %></td>
	        </tr>
	        <tr>
	          <th>위치정보</th>
	          <td ><%=notice_qr.getYard_code() %></td>
	        </tr>
	        <tr>
	          <th>상태정보</th>
	          <td id="cnt_state"><%=notice_qr.getState() %></td>
	        </tr>
	        <tr>
	          <th>무게</th>
	          <td id="weight"><%=notice_qr_weight %>.0 g</td>
	        </tr>
	        <tr>
	          <th>측정된 무게</th>
	          <td id="weight"><%=notice_qr_weight_now %>.0 g</td>
	        </tr>
       </table>
     </div>
     </div>
     </div>
        <div class="row center-align">
         
            <%
            	if(notice_qr.getState().equals("DB오류")){
            		%>            
            		<div class="col s6" style="background-color: red; height: 300px; "></div>
            		<div class="col s6" style="background-color: yellow; height: 300px; opacity: 0.1;"></div>
            	<%}
            	else{
            		%>            
            		<div class="col s6" style="background-color: red; height: 300px; opacity: 0.1;"></div>
            		<div class="col s6" style="background-color: green; height: 300px;"></div>
            		<% 	
            	}
            	%>

          
        </div>
		<script type="text/javascript">
	        
	    </script>
  	</body>
</html>