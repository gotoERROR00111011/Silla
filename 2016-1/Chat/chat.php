<? session_start();
	include "./config/dbconn.php";	
	mysql_query("set names utf8");
	
	if ($_GET['room'] != NULL) {
		$room_no = $_GET['room'];
	} else if ($_POST['room'] != NULL){
		$room_no = $_POST['room'];
	}	
	
	$_SESSION['ss_room'] = $room_no;
	$me_email = $_SESSION['ss_email'];
	$me_name = $_SESSION['ss_name'];
	
	$sql = " SELECT room_member FROM room_list ";
	$sql .= " WHERE room_no = $room_no ";
	$result = mysql_query($sql);
	
	//채팅 참가 리스트
	$room_list;
	if (mysql_num_rows($result) > 0) {
		while ($rows = mysql_fetch_object($result)){
			$room_list .= $rows->room_member . ' ';			
		}
	}	
?>
<?
//이미지 출력

	$sql = " SELECT count(*) as cnt FROM chat ";
	$sql .= " WHERE data_type = 'image' ";
	$result = mysql_query($sql);
	$rows = mysql_fetch_object($result);
	$imgcnt = $rows->cnt;

	$filename = "fileToUpload";	
	$target_dir = "uploads/" . $imgcnt;
	$target_file = $target_dir . basename($_FILES[$filename]["name"]);
	$uploadOk = 1;
	$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
	
	// Check if image file is a actual image or fake image
	if(isset($_POST["submit"])) {
	    //$check = getimagesize($_FILES[$filename]["tmp_name"]);
	    if($check !== false) {
	        //echo "File is an image - " . $check["mime"] . ".";
	        $uploadOk = 1;
	    } else {
	        //echo "File is not an image.";
	        $uploadOk = 0;
	    }
	}
	// Check if file already exists
	if (file_exists($target_file)) {
	    //echo "Sorry, file already exists.";
	    $uploadOk = 0;
	}
	// Check file size
	else if ($_FILES[$filename]["size"] > 500000) {
	    //echo "Sorry, your file is too large.";
	    $uploadOk = 0;
	}
	// Allow certain file formats
	else if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
	&& $imageFileType != "gif" ) {
	    //echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
	    $uploadOk = 0;
	}
	// Check if $uploadOk is set to 0 by an error
	else if ($uploadOk == 0) {
	    //echo "Sorry, your file was not uploaded.";
	// if everything is ok, try to upload file
	} else {
	    if (move_uploaded_file($_FILES[$filename]["tmp_name"], $target_file)) {
	        //echo "The file ". basename( $_FILES[$filename]["name"]). " has been uploaded.";	
			$sql = "INSERT INTO chat (room_no, name, msg, date, data_type) ";
			$sql .= " VALUES ($room_no, '$me_name', '$target_file', NOW(), 'image') ";			
			$result = mysql_query($sql);			
	    } else {
	        //echo "Sorry, there was an error uploading your file.";
	    }
	}
?>
<!DOCTYPE html>
<html lang="ko">
<head>
<title>Ajax Polling Sample Code</title>
	<meta charset="utf-8">
	<script type="text/javascript" src="chat.js"></script>
    <link type="text/css" rel="stylesheet" href="css/default.css" />
    <link type="text/css" rel="stylesheet" href="css/main.css" />
	<link rel="stylesheet" type="text/css" href="css/chat.css" />
</head>
<body>
    <table width="100%" border="0">
  		<tr style="background-color:#000000;">
    		<td><button onClick="exitChat();" style="width:100%;">방 나가기</button></td>
            <td><button onClick="friend()" style="width:100%;">초대하기</button></td>
  		</tr> 
  			<tr>
    			<td colspan="2">채팅방 : <?=$room_no?> <br/> <?=$room_list?></td>
  			</tr>
	</table>
	<dl id="list" style="height:480px; ">
	<?	
		//이전 기록 불러오기
		$sql = " SELECT * FROM chat ";
		$sql .= " WHERE room_no = $room_no ORDER BY date ASC ";
		
		$result = mysql_query($sql);
		
		if (mysql_num_rows($result) > 0) {
			while ($rows = mysql_fetch_object($result)){
				$name = $rows->name;
				$msg = $rows->msg;
				$type = $rows->data_type;
				echo "<dt>".$name."</dt>";	
				if ($type != 'image'){
					echo "<dd>".$msg."</dd>";
				}else {
					echo "<img src='".$msg."' width='200'></img>";
				}
			} 
		}
	?>
    </dl>
	<form onsubmit="chatManager.write(this); return false;">
    	<input name="room" id="room" type="hidden" value="<?=$room_no?>" />
		<input name="name" id="name" type="hidden" value="<?=$_SESSION['ss_name'];?>" />
		<input name="msg" id="msg" type="text"/>
		<input name="btn" id="btn" type="submit" value="입력"/>
	</form>
    <form action="chat.php" method="post" enctype="multipart/form-data">     
    	<input name="room" id="room" type="hidden" value="<?=$room_no?>" />
		<input name="name" id="name" type="hidden" value="<?=$_SESSION['ss_name'];?>" />
        <input name="fileToUpload" id="fileToUpload" type="file"/>        
		<input name="image" id="image" type="submit" value="이미지 입력"/>
    </form>
</body>
<script>
	function exitChat(){
		location.replace("room_select.php");
	}
	function friend(){
		window.open('friend_select.php','popup','toolbar=no,location=no,status=no,menubar=no,scrollbars=no,resizable=yes,width=300,height=300');
	}
</script>
</html>
