<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ page import="seaitc.*" %>
    <%
			String id2 = request.getParameter("id2");
    		String id = request.getParameter("id");
			String pw = request.getParameter("pw");
			/* String level = request.getParameter("level");
			String t_code = request.getParameter("t_code");  */
	%>
<%-- 	<script>
	sessionStorage.setItem("level",<%=level %>);
	sessionStorage.setItem("t_code",<%=t_code %>);
	</script> --%>
{
	"id" : "<%= id %>",
	"pw" : "<%= pw %>"
<%-- 	"level" : "<%= level %>",
	"t_code" : "<%= t_code %>"  --%>
}