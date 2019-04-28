<?php
	$set_domain = "localhost";
	$set_id = "root";
	$set_pw = "apmsetup";
	$dbname = "chat";
	$dbconn = mysql_connect($set_domain, $set_id, $set_pw);
	if (!$dbconn)
	{
		echo("#001. Database Connection Error !!!");
		exit;	
	}
	$status = mysql_select_db("chat", $dbconn);
	if (!$status)
	{
		echo("#002. Database Select Error !!!");
		exit;	
	}
?>