# Time Table Share  

신라대학교 3학년 2학기  
산학실무 프로젝트 II  

[![TimeTableShare](https://img.youtube.com/vi/EOXanZYigNE/0.jpg)](https://www.youtube.com/watch?v=EOXanZYigNE)
(Youtube)[https://www.youtube.com/watch?v=EOXanZYigNE&t=119s]  

mongoDB

Collections

user  
_id:String(email), pw:String, name:String, lat:Number, lon:Number, call:String

friend    
_id(auto), me:String, friend:String, friend_name:String

room  
_id:(auto), user:[String], name:[String]

chat  
_id:(auto), user:String, date:new Date(), msg:String, room_id:String

lecture   
_id:(auto), day(day of the week), lec:String, room:String, prof:String, user:String(email), name:[String]

mongodb
- use timetable
- db.craeteCollection("user", {pw:String, name:String, lat:Number, lon:Number, call:String})
- autoIndex: true
