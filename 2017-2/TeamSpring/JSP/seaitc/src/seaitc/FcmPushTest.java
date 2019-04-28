package seaitc;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import org.json.simple.JSONObject;

public class FcmPushTest {

    // Method to send Notifications from server to client end.

    public final static String AUTH_KEY_FCM = "AAAAG1Z5O84:APA91bEqwjqkzb7IbylA5OPxJmnl81zDDRBKBaLJJwSy2C4WKyCyYLUOAXpfaaBND-f17-jEBEzwolB4KIgMrzJhXUoTzbqhsagIoq-u5xDfDFXfScZQ2gnR4Z65NzQ6xJwgZKVRfet6";
    public final static String API_URL_FCM = "https://fcm.googleapis.com/fcm/send";

    // userDeviceIdKey is the device id you will query from your database

    public static void pushFCMNotification(String userDeviceIdKey)
            throws Exception {
        String authKey = AUTH_KEY_FCM; // You FCM AUTH key
        String FMCurl = API_URL_FCM;

        URL url = new URL(FMCurl);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();

        conn.setUseCaches(false);
        conn.setDoInput(true);
        conn.setDoOutput(true);
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Authorization", "key=" + authKey);
        conn.setRequestProperty("Content-Type", "application/json");

        JSONObject json = new JSONObject();
        JSONObject info = new JSONObject();

        info.put("body", "푸쉬 발송 테스트 입니다."); // Notification body
        info.put("sound", "default");
        json.put("notification", info);
        json.put("to", userDeviceIdKey.trim()); // deviceID

        try(OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream())){
//혹시나 한글 깨짐이 발생하면 
//try(OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream(), "UTF-8")){ 인코딩을 변경해준다.

            wr.write(json.toString());
            wr.flush();
        }catch(Exception e){
        }

        if (conn.getResponseCode() != HttpURLConnection.HTTP_OK) {
            throw new RuntimeException("Failed : HTTP error code : " + conn.getResponseCode());
        }

        BufferedReader br = new BufferedReader(new InputStreamReader(
                (conn.getInputStream())));

        String output;
        System.out.println("Output from Server …. \n");
        while ((output = br.readLine()) != null) {
            System.out.println(output);
        }

        conn.disconnect();
    }
/*
    public static void main(String a[]) throws Exception{
        try{
            FcmPushTest.pushFCMNotification("/topics/all");
        }catch(Exception e){
            e.printStackTrace();
        }
    }
*/
}