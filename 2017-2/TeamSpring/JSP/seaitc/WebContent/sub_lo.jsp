<%@page import="java.util.ArrayList"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>   
<%@ page import="java.sql.*" %>
<%
    request.setCharacterEncoding("UTF-8");
	String t_code = request.getParameter("t_code");
	String id = (String)session.getAttribute("id");
	String t_code_session = (String)session.getAttribute("t_code");
	String level = (String)session.getAttribute("level");


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
 <script type="text/javascript">
  $(document).ready(function() {
	
	/* if($(".yard_state_val").val()=='1')
	{
		var y_state = $(".yard_state_val").attr("value");
		alert(y_state);
	} */		  
	  
    $(".yard_table").click(function() {
        var y_code = $(this).attr("id");
        var y_state = $(this).attr("value");
        alert("y_code : " +y_code );
        alert("y_state : " +y_state );
        sessionStorage.setItem("y_code", y_code);
        location.href="submain_yard_login_detail.jsp?c_code="+y_code+"&y_state="+y_state;
    });
	 $(".con_list").click(function() {
	        var c_code = $(this).attr("value");
	        alert("c_code : " +c_code );
	        sessionStorage.setItem("c_code", c_code);
	        location.href="submain_container_detail.jsp?c_code="+c_code;
	    });
    $("#yard_state").hide();
    $("#work_block").click(function() {
    	$("#tab1_first").hide(); 
    	$("#yard_state").show();
    });
    $("#yard").click(function() {
    	alert("권한이 없거나 로그인이 필요합니다.");
    });
    $("#w_yard").click(function() {
    	$("#tab1_first").hide(); 
    	$("#yard_state").show();
    	 
    });
    $("#searchInput").on("keyup", function() {
        var value = $(this).val().toLowerCase();
        $(".con_list").filter(function() {
          $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1)
        });
    });
    
  });
</script>
  <style type="text/css">
  h2{
    font-weight: bolder;
  }
  .navbar{
    background-color: #033f77;
    color: white;
  }
  .sub_title{
    font-weight: bolder;
  }
  .tab-content{
    margin-left: 10px;
  }
  .tab_head{
    text-align: center;
    background-color: #F6F6F6;
    /*vertical-align: middle;*/
  }
  .tab3_finish{
    color: red;
  }
  .tab3_schedule{
    color: blue;
  }
  .yard_line_basic{
    border: 1px solid black
  }
  .yard_line_basic1{
    border: 1px solid green
  }
  .yard_line_woring{
    border: 2px solid green;
  }
  .yard_line_accident{
    border: 2px solid red;
  }
  .tab1_row{
    margin-top: 10px;
    margin-bottom: 5px;
    margin-right: 5px;
  }
  .yard_working{
    font-weight: bold;
    color: green;
  }
  .yard_accident{
    font-weight: bold;
    color: red;
  }
  #img_logo{
    width: 100%;
    height: 100%;
    margin-left: 10px;
  }
</style>
</head>
<body>
  <header>
    <nav class="navbar">
      <div class="col-xs-2">
        <ul class="nav navbar-nav navbar-left">
          <li><a href="main.jsp">Back</a></li>
        </ul>
      </div>
      <div class="col-xs-8">
        <h1 class="navbar-text" style="font-style: italic;">SMART PORT</h1>
      </div>
      <div class="col-xs-2">
        <ul class="nav navbar-nav navbar-right">
          <li>
          	<%if(session.getAttribute("id") == null){ %>
          	<a href="login.jsp">Login</a>
          	<%}
          	else{ %>
          	<a href="logout.jsp">LogOut</a>
          <%	}%>
          </li>
        </ul>
      </div>
    </nav>
  </header>
  <div class="container">
    <div class="row">
     <%
		  request.setCharacterEncoding("UTF-8");
		  Connection t_con = null;
		  PreparedStatement t_pstmt = null;
		  ResultSet t_rs = null;
		 System.out.println("터미널 코드  세션 "+t_code);
		   /* int count=1; */
		   
		   String t_name , t_adress , t_tel;
   
		
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		
		t_con = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String t_SQL = "select * from port_terminal where terminal_code ='"+ t_code+"'";
       t_pstmt = t_con.prepareStatement(t_SQL);
       System.out.print("DB sql 삽입");
       t_rs = t_pstmt.executeQuery();
       if(t_rs.next())
       {
    	   t_name=t_rs.getString(2);
    	   t_adress=t_rs.getString(3);
    	   t_tel=t_rs.getString(4);
    	   
     %>
	
      <div class="col-xs-3" style="padding: 3px;">
        <img id="img_logo" src="img/Logo_BCTOC.png">
      </div>
      <div class="col-xs-9">
        <div class="row" style="text-align: center;">
         <%--  <h2><%=ship_name %></h2> --%>
   
        </div>
        <div class="row">
          <div class="col-xs-3 sub_title" style="padding: 0px 0px 0px 20px;">주소</div><!-- padding : top right bottom left-->
          <div class="col-xs-9"><%= t_adress %></div>
        </div>
        <div class="row">
          <div class="col-xs-3 sub_title" style="padding: 0px 0px 0px 20px;">연락처</div>
          <div class="col-xs-9"><%= t_tel %></div>
        </div>
        <%
        }
    }
    catch(Exception e)
    {
       
     }
    if(t_rs!=null)t_rs.close();
    if(t_pstmt!=null)t_pstmt.close();
    if(t_con!=null)t_con.close();
     %>
      </div>
    </div>
    <div class="row" style="height: 5px;"></div>
    <div class="row">
      <ul class="nav nav-tabs">
        <li class="active"><a data-toggle="tab" href="#tab1">야드 작업 현황</a></li>
        <li><a data-toggle="tab" href="#tab2">본선 작업 현황</a></li>
        <li><a data-toggle="tab" href="#tab3">컨테이너 검색</a></li>
      </ul>
      
      <div class="tab-content">
        <div id="tab1" class="tab-pane fade in active" style="text-align: center;">
        <div id="tab1_first">
        <div id="tab1" class="tab-pane fade in active">
          <p style="color: gray; margin-top: 10px;">*작업블록 선택시 상세정보를 확인하실 수 있습니다.</p>
          <table class="table" style="text-align: center;">
            <thead>
              <tr class="active">
              	<%
              	if( id != null) {
              	
              	/*  if(t_code=''''=t_code_session ||level.equals("9")){ */
              		 if(level.equals("9")){
              	%>
                	<a href="#"><th rowspan="2" class="tab_head" style="vertical-align: middle; cursor:pointer;" id="work_block" >작업블록</th></a>
                <% 
              	 	}else if(t_code.equals(t_code_session)){
              			%><a href="#"><th rowspan="2" class="tab_head" style="vertical-align: middle; cursor:pointer;" id="work_block" >작업블록</th></a>
          				<% 
              		 }
              		else {
                      	%>
                      	  
                        <a href="#"><th rowspan="2" class="tab_head" style="vertical-align: middle; cursor:pointer;" id="yard">작업블록</th></a>
                        <%} 
              	}
              	else {
              	%>
              		
                	<a href="#"><th rowspan="2" class="tab_head" style="vertical-align: middle; cursor:pointer;" id="yard">작업블록</th></a>
                <%} %>
                <td colspan="2" class="tab_head">목표량</td>
                <td colspan="2"  class="tab_head">현재량</td>
              </tr>
              <tr class="active">
                <th class="tab_head">반출입</th>
                <th class="tab_head">본선</th>
                <th class="tab_head">반출입</th>
                <th class="tab_head">본선</th>
              </tr>
            </thead>
            <tbody>
            <%
            request.setCharacterEncoding("UTF-8");
            Connection y_con = null;
            PreparedStatement y_pstmt = null;
            ResultSet y_rs = null;
            
            /* int count=1; */
            
            String working_yard, terminal_code, goals_working ,goals_ship,present_working ,present_ship;
            try{
            	Class.forName("com.mysql.jdbc.Driver");
        		
        		String dbURL ="jdbc:mysql://localhost:3306/ado";
        		String dbID = "root";
        		String dbPassword = "1111";
        		
        		y_con = DriverManager.getConnection(dbURL,dbID,dbPassword);
        		
               String y_SQL = "select * from port_yard where terminal_code = '"+t_code+"'";
               y_pstmt = y_con.prepareStatement(y_SQL);
               System.out.print("DB sql 삽입2");
               System.out.print(y_SQL);
               y_rs = y_pstmt.executeQuery();
               while(y_rs.next())
               {
            	   //System.out.print("?");
            	   working_yard=y_rs.getString(1);
            	   terminal_code=y_rs.getString(2);
            	   goals_working=y_rs.getString(3);
            	   goals_ship=y_rs.getString(4);
            	   present_working=y_rs.getString(5);
            	   present_ship=y_rs.getString(6);
            	   
             %>      
              <tr>
                <td id="w_yard"><%= working_yard %></td>
                <td><%= goals_working %></td>
                <td><%= goals_ship %></td>
                <td><%= present_working %></td>
                <td><%= present_ship %></td>
              </tr> 
             <%
              }
               System.out.print("DB 검색 후 뽑기");
            }
               catch(Exception e)
               {
                  
                }
               finally{
               
                      if(y_rs!=null)y_rs.close();
                      if(y_pstmt!=null)y_pstmt.close();
                      if(y_con!=null)y_con.close();
               }    
              %>
            </tbody>
          </table>
          </div>
        </div>
        <%
	        Connection yard_con = null;
	        PreparedStatement yard_stmt = null;
	        ResultSet yard_rs = null;
	        
	        ArrayList<String> listA = new ArrayList<String>();
	        
	        
	        try{
				Class.forName("com.mysql.jdbc.Driver");
        		
        		String dbURL ="jdbc:mysql://localhost:3306/ado";
        		String dbID = "root";
        		String dbPassword = "1111";
        		
        		yard_con = DriverManager.getConnection(dbURL,dbID,dbPassword);
        		
        		String a;
	            String y_SQL2 = "select working_yard,port_state from port_yard";
	            yard_stmt = yard_con.prepareStatement(y_SQL2);
	            System.out.println("DB sql 삽입3");
	            System.out.print(y_SQL2);
	            yard_rs = yard_stmt.executeQuery();
	            
	            while(yard_rs.next()){
	            	String yard=yard_rs.getString(1);
	            	String state= yard_rs.getString(2);
	            	if((yard_rs.getString(2)).equals("작업중")){
	            		 a = "작업중";
	            	}else if((yard_rs.getString(2)).equals("사고완료")){
	            		 a = "사고완료";
	            	}
	            	else {
	            		 a = "1";
	            	}
	            	System.out.println("루프3");
	            	//list.add(a);
	            	System.out.println(yard);
	            	System.out.println(state);
	            	listA.add(yard);
	            	listA.add(state);
	            	//System.out.println(list.size());
	            }
		     	
	        }catch(Exception e){
	       
			}finally{
				
			}
	     
        %>
        <div style="margin: 25px;"></div>
       <div id="yard_state">
       <%
       for(int i=1; i<listA.size();i=i+2)
       {
    	   if((i+1)%6 !=0){
    	%> 
    	<div class="col-xs-4" >
             <a href="#" class="yard_table"  id="<%=listA.get(i-1).toString()%>" value="<%=listA.get(i).toString()%>">
              <p class="yard_state_val" id="test"+i  value="<%=listA.get(i).toString()%>"><%=listA.get(i-1).toString()%><%=listA.get(i).toString()%></p>
              </a>
              <table class="yard_line_basic" style="width: 100%;" id="<%=listA.get(i-1).toString()%>_id"  >
                <tr class="yard_line_basic">
                  <td class="yard_line_basic">1</td>
                  <td class="yard_line_basic">2</td>
                  <td class="yard_line_basic">3</td>
                </tr>
                <tr>
                  <td class="yard_line_basic">1</td>
                  <td class="yard_line_basic">2</td>
                  <td class="yard_line_basic">3</td>
                </tr>
              </table>
            </div>
       
           	 
    	<%
    	   }
    	   else if((i+1)%6==0)
    		{
    		%>
    		<div class="col-xs-4" >
             <a href="#" class="yard_table" id="<%=listA.get(i-1).toString()%>" value="<%=listA.get(i).toString()%>">
              <p class="yard_state_val" id="test"+i <%-- id="<%=listA.get(i-1).toString()%>" --%> value="<%=listA.get(i).toString()%>"><%=listA.get(i-1).toString()%><%=listA.get(i).toString()%></p>
              </a>
              <table class="yard_line_basic" style="width: 100%" id="<%=listA.get(i-1).toString()%>_id" >
                <tr class="yard_line_basic">
                  <td class="yard_line_basic">1</td>
                  <td class="yard_line_basic">2</td>
                  <td class="yard_line_basic">3</td>
                </tr>
                <tr>
                  <td class="yard_line_basic">1</td>
                  <td class="yard_line_basic">2</td>
                  <td class="yard_line_basic">3</td>
                </tr>
              </table>
            </div>
            <div style="margin: 25px;"></div>
    		<% 
    		}
    	%>
	    		 		
	   <%
    	} 	
       %>
       </div> 
      </div>
      
     
     
   		<script type="text/javascript">
   	 <%
		
		for(int i=0;i<=23;i=i+2)
		{
			%>
				alert($("#yard_state_val").text());
  				var a = "#<%=listA.get(i).toString()%>"; 
  				//1A 제목 id
  				var yard_table = "<%=listA.get(i).toString()%>_id";
  				//1A_id table에 id
  				var yard_state = $(a).attr("value");
  				$(a).css("color","black");
  				if (yard_state == "작업중" ){
  					$(a).css("color","green");
  					
  					$("#"+yard_table+" td").attr("class","yard_line_basic1");
  					//var yard_line_style = $(yard_line_basic).attr("class",yard_line_style);
  					//$(yard_style).css("color","green");
  					//$(yard_line_style).css("color","green");
  				}
  				if(yard_state == "사고발생"){
  				 	$(a).css("color","red");
  				 	$(yard_table).css("color","red");
  				 	//$(yard_line_style).css("color","red");
  				}
  				if(yard_state!="작업중"&&yard_state!="사고발생")
  				{
  					$(a).text("<%=listA.get(i).toString()%>");
  					
  				}
				//console.log(b);
  				<%
   			}
   			%>
  		
		</script>
			
   			
   			
     
  <%
   request.setCharacterEncoding("UTF-8");
   Connection conn2 = null;
   PreparedStatement pstmt2 = null;
   ResultSet rs2 = null;
   Connection conn2_1 = null;
   PreparedStatement pstmt2_1 = null;
   ResultSet rs2_1 = null;
   /* int count=1; */
   
   String ship_name , in_date , out_date ,max_work,now_work ,rest_work ;
   String ship_name2 , in_date2 , out_date2 ,max_work2, now_work2,rest_work2;
   
%>
	 <div id="tab2" class="tab-pane fade">
<%
    
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		
		conn2 = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String SQL2 = "select * from ship where ship_name='HEUNG-A SARAHb'";
       String SQL2_1 = "select * from ship where ship_name='HEUNG-A SARAHc'";
     
       pstmt2 = conn2.prepareStatement(SQL2);
       System.out.print("DB sql 삽입2");
       rs2 = pstmt2.executeQuery();
       pstmt2_1 = conn2.prepareStatement(SQL2_1);
       System.out.print("DB sql 삽입");
       rs2_1 = pstmt2_1.executeQuery();
      if(rs2.next())
       {
    	   ship_name = rs2.getString("ship_name");
    	   in_date = rs2.getString("in_date");
    	   out_date =rs2.getString("out_date");
    	   max_work =rs2.getString("max_work");
    	   now_work =rs2.getString("now_work");
    	   rest_work =rs2.getString("rest_work");
    	   
    	   if(rs2_1.next())
    	   {
    		   ship_name2 = rs2_1.getString("ship_name");
        	   in_date2 = rs2_1.getString("in_date");
        	   out_date2 =rs2_1.getString("out_date");
        	   max_work2 =rs2_1.getString("max_work");
        	   now_work2 =rs2_1.getString("now_work");
        	   rest_work2 =rs2_1.getString("rest_work");
    	   
	%>
       
        <table class="table" style="text-align: center; margin-top: 10px;">
          <thead>
            <tr>
              <th class="tab_head" style="vertical-align: middle;">선석</th>
              <td colspan="2"><img src="img/shipping.png" style="height: 80px;"></td>
              <td colspan="2"><img src="img/shipping.png" style="height: 80px;"></td>
            </tr>
            <tr>
              <th class="tab_head">선박명</th>
              <td colspan="2"><%=ship_name %></td>
              <td colspan="2"><%=ship_name2 %></td>
            </tr>
            <tr>
              <th class="tab_head">입항일시</th>
              <td colspan="2"><%=in_date %></td>
              <td colspan="2"><%=in_date2 %></td>
            </tr>
            <tr>
              <th class="tab_head">출항일시</th>
              <td colspan="2"><%=out_date %></td>
              <td colspan="2"><%=out_date2 %></td>
            </tr>
            <tr>
              <th class="tab_head">구분</th>
              <td>양하</td>
              <td>적하</td>
              <td>양하</td>
              <td>적하</td>
            </tr>
            <tr>
              <th class="tab_head">작업수</th>
              <td><%=max_work %>/<%=now_work %>/<%=rest_work %></td>
            </tr>
          </thead>
          <tbody>
       <%
    	   }
      	 }
   	 }
      catch(Exception e)
      {
         
       }
             if(rs2!=null)rs2.close();
             if(pstmt2!=null)pstmt2.close();
             if(conn2!=null)conn2.close();
             if(rs2_1!=null)rs2_1.close();
             if(pstmt2_1!=null)pstmt2_1.close();
             if(conn2_1!=null)conn2_1.close();
      

       %> 
          </tbody>
        </table>
      </div>
      
      <div id="tab3" class="tab-pane fade">
        
        <div class="row" style="margin-bottom: 10px; margin-top: 10px;" >
	        <div class="col-xs-1">
	        </div>
	        <div class="col-xs-10">
	           	<input class="form-control" id="searchInput" type="text" placeholder="검색할 정보를 입력하세요.">
	        </div>
        </div>
        
        <table class="table" style="text-align: center;">
          <thead>
            <tr class="active">
              <th class="tab_head">코드번호</th>
              <th class="tab_head">상태정보</th>
              <th class="tab_head">작업일시</th>
              <th class="tab_head">모선정보</th>
            </tr>
          </thead>
          <tbody>
      <%
   request.setCharacterEncoding("UTF-8");
   Connection list_con = null;
   PreparedStatement list_pstmt = null;
   ResultSet list_rs = null;
   /* int count=1; */
   
   
   ArrayList<String> con_list = new ArrayList<String>();
 /*   ArrayList<listB> listB = new ArrayList<listB>(); */
   
   try{
		Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		
		list_con = DriverManager.getConnection(dbURL,dbID,dbPassword);

       String C_SQL = "select * from container where terminal_code = '"+t_code+"'";
       list_pstmt = list_con.prepareStatement(C_SQL);
       System.out.println("DB 검색 sql2222");
       System.out.print(C_SQL);
       list_rs = list_pstmt.executeQuery();
       
       while(list_rs.next())
       {
     	    
 	       	String c_code = list_rs.getString("cnt_code");
 	      	String c_state = list_rs.getString("cnt_state");
 	      	String w_time = list_rs.getString("w_time");
 	      	String ship = list_rs.getString("ship_name");
 	    	
      
       %>
     
             <tr class="con_list" value="<%=c_code %>">
              <td><%=c_code %></td>
              <td class="tab3_schedule"><%=c_state%></td>
              <td><%= w_time %></td>
              <td><%=ship %></td>
            </tr>
           
       <%
	    	}
	    	}
		   catch(Exception e)
		   {
		      
		   }
          if(list_rs!=null)list_rs.close();
          if(list_pstmt!=null)list_pstmt.close();
          if(list_con!=null)list_con.close();
          
         
       %>
			
          
            <!-- <tr>
              <td>AMC891214D</td>
              <td class="tab3_finish">양하완료</td>
              <td>2017-08-14 22:15</td>
              <td>BE911W</td>
            </tr>
            <tr>
              <td>U9261707AMC</td>
              <td class="tab3_finish">양하완료</td>
              <td>2016-12-08 11:57</td>
              <td>CMA</td>
            </tr> -->
      
      
   
          </tbody>
        </table>
        </div>
      </div>
    </div>
  </div>  
</body>
</html>
