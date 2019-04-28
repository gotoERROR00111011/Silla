<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="java.sql.*"
    import ="java.io.BufferedReader"
	import="java.io.InputStreamReader"
	import="java.io.OutputStreamWriter"
	import="java.net.HttpURLConnection"
	import="java.net.URL"
	import="org.json.simple.JSONObject"
	import="seaitc.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>a</title>
</head>
<body>

<%
	
	Connection conn =null;
	PreparedStatement pstmt =null;	
	String code= request.getParameter("a");
	
	Connection conn2 =null;
	PreparedStatement pstmt2 =null;	
	
	
	
	
%>

 <%
 	int n=0;
 	int p=0;
 	try{
 		Class.forName("com.mysql.jdbc.Driver");
 		conn = DriverManager.getConnection(
 				"jdbc:mysql://localhost:3306/ado?characterEncoding=utf8", 
 				"root", 
 				"1111");
 		conn2 = DriverManager.getConnection(
 				"jdbc:mysql://localhost:3306/ado?characterEncoding=utf8", 
 				"root", 
 				"1111");
 	
 		String SQL = "update container set cnt_state='사고발생' where cnt_state='작업중' and terminal_code = 'BCTOC' and working_yard ='2C'";
		String SQL2 = "update port_yard set port_state='사고발생' where terminal_code = 'BCTOC' and working_yard ='2C'";
 		//System.out.println(SQL);
		try {
			pstmt = conn.prepareStatement(SQL);
			pstmt.executeUpdate();
			
			pstmt2 = conn2.prepareStatement(SQL2);
			n = pstmt2.executeUpdate();
			
		}catch(Exception e){
			e.printStackTrace();
		}
 		
 	
 		}catch(SQLException e)
		{
			
		 }finally{
			 try{
				 if(pstmt!=null)pstmt.close();
				 if(conn!=null)conn.close();
			 }
			 catch(SQLException e){
				 
			 }
		 }
 			 
 	 %>
 	 	

 	 	
 	 	<%
 	 		if(n != 0)
 	 		{

 	 			FcmPushTest FcmPushTest = new FcmPushTest(); 
 	 			try{
 	 			    FcmPushTest.pushFCMNotification("/topics/all");
 	 			}catch(Exception e){
 	 			    e.printStackTrace();
 	 			}
 	 			
 	 			//FcmPushTest FcmPushTest = new FcmPushTest(); 
 	 	%>
 	 		<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>
 	 		<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>	
 	 		<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>		
 	 		<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>	<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>	<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>	<script type="text/javascript">
 	 			alert('입력되었습니다..');
 	 			
 	 		</script>	
 	 	<% 
 	 		}
 	 	%>
 	 	
 	 	
	
	
</body>
</html>