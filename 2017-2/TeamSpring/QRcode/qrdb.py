from pyzbar.pyzbar import decode
import cv2
import time

import pymysql
conn = pymysql.connect(host='localhost', user='root', password='1111', db='ado', charset='utf8')
#curs = conn.cursor()

#conn2 = pymysql.connect(host='localhost', user='root', password='1111', db='ado', charset='utf8')
#curs2 = conn.cursor()

cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

while(1):
	ret, frame = cap.read()
	cv2.imshow('frame', frame)
	cv2.waitKey(1)

	allCodes = decode(frame)

	if len(allCodes) > 0:
		for code in allCodes:
			data = str(code.data)
			data = data[2:-1]
			print(data)
			
			# data = 'AMCU9261707'
			
			conn = pymysql.connect(host='localhost', user='root', password='1111', db='ado', charset='utf8')
			curs = conn.cursor()				
			sql = "update container set cnt_state = '작업중' where cnt_code = '"+ data +"'"
			curs.execute(sql)
			conn.commit()	
			sql = "select * from container where cnt_code = '" +data+ "' and terminal_code = 'BCTOC' and working_yard = '2C'"
			result = curs.execute(sql)
			conn.commit()

			if result==1:
				sql = "update port_yard set port_state = '작업중' where working_yard  = '2C'"
				curs.execute(sql)
				conn.commit()
			sql = "select * from container where cnt_code = '"+data+"'"
			result = curs.execute(sql)
			if result==1:		
				sql = "UPDATE  ado.notice_qr SET  container_code = '"+data+"', state = '확인'"  ;
				curs.execute(sql)
				conn.commit()	
			else :
				sql = "UPDATE  ado.notice_qr SET  container_code = '"+data+"', state = 'DB오류'"  ;
				curs.execute(sql)
				conn.commit()	
			curs.close()
			conn.close()
			
			time.sleep(18)			
			
			conn = pymysql.connect(host='localhost', user='root', password='1111', db='ado', charset='utf8')
			curs = conn.cursor()			
			sql = "update container set cnt_state = '이상없음' where cnt_code = '"+ data +"' and cnt_state = '작업중'"
			curs.execute(sql)
			conn.commit()			
			sql = "UPDATE port_yard set port_state = '이상없음' where working_yard = '2C' and port_state = '작업중'"
			curs.execute(sql)
			conn.commit()			
			curs.close()
			conn.close()			
			
	time.sleep(0.2)
