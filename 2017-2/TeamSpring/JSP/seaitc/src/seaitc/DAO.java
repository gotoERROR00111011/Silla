package seaitc;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

import org.json.simple.*;
import org.json.simple.parser.JSONParser;


public class DAO {
	private PreparedStatement pstmt=null;
	private ResultSet rs=null;
	Connection conn;
	
	public void connect() throws NamingException, SQLException
	{

		Context initContext = new InitialContext();
		DataSource ds = (DataSource)initContext.lookup("java:/comp/env/jdbc/mysql");
		conn = ds.getConnection();		
	}

	public User login(String id,String pw) throws SQLException , NamingException {
		connect();
		
		String SQL = "select * from user where id='"+id+"'and password = '"+pw+"'";
		System.out.println(SQL);
		User user = new User();
		try {
			pstmt = conn.prepareStatement(SQL);
			rs=pstmt.executeQuery();
			
			if(rs.next()) {
				user.setId(rs.getString(1));
				user.setPw(rs.getString(2));

			}
	     	rs.close();
	        pstmt.close();
	        conn.close();
	        
		}catch(Exception e) {
			
		}
		return user;
	}
	public ArrayList<port_yard> port_yard (String t_code) throws NamingException, SQLException{
		connect();
		String SQL = "select * from port_yard where terminal_code ='"+t_code+"'";
		System.out.println(SQL);
		
		ArrayList<port_yard> list = new ArrayList<port_yard>();
		
		try {
			System.out.println("a");
			pstmt = conn.prepareStatement(SQL);
			System.out.println("b");
			rs=pstmt.executeQuery();
			
			while(rs.next()) {
				port_yard port_yard = new port_yard();
				port_yard.setWorking_yard(rs.getString(1));
				port_yard.setTerminal_code(rs.getString(2));
				port_yard.setGoals_working(rs.getInt(3));
				port_yard.setGoals_ship(rs.getInt(4));
				port_yard.setPresent_working(rs.getInt(5));
				port_yard.setPresent_ship(rs.getInt(6));
				port_yard.setPort_state(rs.getString(7));
				System.out.println(rs.getString(7));
				list.add(port_yard);
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return list;
		
	}
	public ArrayList<ship> ship (String t_code) throws NamingException, SQLException{
		connect();
		String SQL = "select * from ship where terminal_code ='"+t_code+"'";
		System.out.println(SQL);
		
		ArrayList<ship> list = new ArrayList<ship>();
		
		try {
			//System.out.println("a");
			pstmt = conn.prepareStatement(SQL);
			//System.out.println("b");
			rs=pstmt.executeQuery();
			
			while(rs.next()) {
				ship ship = new ship();
				ship.setShip_name(rs.getString(1));
				ship.setTerminal_code(rs.getString(2));
				ship.setIn_date(rs.getString(3));
				ship.setOut_date(rs.getString(4));
				ship.setMax_work(rs.getInt(5));
				ship.setNow_work(rs.getInt(6));
				ship.setRest_work(rs.getInt(7));
				//System.out.println(rs.getString(7));
				list.add(ship);
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return list;
		
	}
	public ArrayList<container> container (String t_code) throws NamingException, SQLException{
		connect();
		String SQL = "select * from container where terminal_code ='"+t_code+"'";
		System.out.println(SQL);
		
		ArrayList<container> list = new ArrayList<container>();
		
		try {
			System.out.println("a");
			pstmt = conn.prepareStatement(SQL);
			System.out.println("b");
			rs=pstmt.executeQuery();
			
			while(rs.next()) {
				container container = new container();
				container.setCnt_code(rs.getString(1));
				container.setTerminal_code(rs.getString(2));
				container.setShip_name(rs.getString(3));
				container.setCnt_operation(rs.getString(4));
				container.setCnt_state(rs.getString(5));
				container.setW_time(rs.getString(6));
				container.setYard_bay(rs.getString(7));
				container.setYard_row(rs.getString(8));
				container.setYard_tir(rs.getString(9));
				container.setShip_name(rs.getString(10));
				container.setVehicle_ship(rs.getString(11));
				container.setInOut_separation(rs.getString(12));
				container.setCnt_load_state(rs.getString(13));
				container.setCar_num(rs.getString(14));
				container.setConsignee(rs.getString(15));
				container.setSend(rs.getString(16));
				container.setBL_code(rs.getString(17));
				//System.out.println(rs.getString(7));
				list.add(container);
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return list;
		
	}
	public container yard_container (String t_code,String working_yard,String state) throws NamingException, SQLException{
		connect();
		String SQL = "select * from container where terminal_code ='"+t_code+"' and working_yard = '"+working_yard+"' and cnt_state='"+state+"'";
		System.out.println(SQL);
		
		ArrayList<container> list = new ArrayList<container>();
		container container = new container();
		try {
			//System.out.println("a");
			pstmt = conn.prepareStatement(SQL);
			//System.out.println("b");
			rs=pstmt.executeQuery();
			
			if(rs.next()) {
				
				container.setCnt_code(rs.getString(1));
				container.setTerminal_code(rs.getString(2));
				container.setWorking_yard(rs.getString(3));
				container.setShip_name(rs.getString(4));
				container.setCnt_operation(rs.getString(5));
				container.setCnt_state(rs.getString(6));
				container.setW_time(rs.getString(7));
				container.setYard_bay(rs.getString(8));
				container.setYard_row(rs.getString(9));
				container.setYard_tir(rs.getString(10));
				container.setVehicle_ship(rs.getString(11));
				container.setInOut_separation(rs.getString(12));
				container.setCnt_load_state(rs.getString(13));
				container.setCar_num(rs.getString(14));
				container.setConsignee(rs.getString(15));
				container.setSend(rs.getString(16));
				container.setBL_code(rs.getString(17));
				//System.out.println(rs.getString(7));
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return container;
		
	}public container container_detail (String t_code,String c_code) throws NamingException, SQLException{
	      connect();
	      String SQL = "select * from container where terminal_code ='"+t_code+"' and cnt_code = '"+c_code+"'";
	      System.out.println(SQL);
	      
	      
	      container container = new container();
	      try {
	         //System.out.println("a");
	         pstmt = conn.prepareStatement(SQL);
	         //System.out.println("b");
	         rs=pstmt.executeQuery();
	         
	         if(rs.next()) {
	            
	            container.setCnt_code(rs.getString(1));
	            container.setTerminal_code(rs.getString(2));
	            container.setWorking_yard(rs.getString(3));
	            container.setShip_name(rs.getString(4));
	            container.setCnt_operation(rs.getString(5));
	            container.setCnt_state(rs.getString(6));
	            container.setW_time(rs.getString(7));
	            container.setYard_bay(rs.getString(8));
	            container.setYard_row(rs.getString(9));
	            container.setYard_tir(rs.getString(10));
	            container.setVehicle_ship(rs.getString(11));
	            container.setInOut_separation(rs.getString(12));
	            container.setCnt_load_state(rs.getString(13));
	            container.setCar_num(rs.getString(14));
	            container.setConsignee(rs.getString(15));
	            container.setSend(rs.getString(16));
	            container.setBL_code(rs.getString(17));
	            //System.out.println(rs.getString(7));
	         }
	      }catch(Exception e) {
	         System.out.println(e);
	      }      
	      return container;
	      
	   }
	public ArrayList<notice_qr> notice_qr (String time) throws NamingException, SQLException{
		connect();
		String SQL = "select * from notice_qr where time ='"+time+"'";
		System.out.println(SQL);
		
		ArrayList<notice_qr> list = new ArrayList<notice_qr>();
		
		try {		
			pstmt = conn.prepareStatement(SQL);
			rs=pstmt.executeQuery();
			
			while(rs.next()) {
				notice_qr notice_qr = new notice_qr();
				notice_qr.setContainer_code(rs.getString(1));
				notice_qr.setTerminal_code(rs.getString(2));
				notice_qr.setYard_code(rs.getString(3));
				notice_qr.setState(rs.getString(4));
				notice_qr.setTime(rs.getString(5));
				list.add(notice_qr);
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return list;
		
	}
	public ArrayList<notice_qr> notice_qr_new () throws NamingException, SQLException{
		connect();
		String SQL = "select * from notice_qr where newst ='1' and terminal_code = 'BCTOC'";
		System.out.println(SQL);
		
		ArrayList<notice_qr> list = new ArrayList<notice_qr>();
		
		try {		
			pstmt = conn.prepareStatement(SQL);
			rs=pstmt.executeQuery();
			
			while(rs.next()) {
				notice_qr notice_qr = new notice_qr();
				notice_qr.setContainer_code(rs.getString(1));
				notice_qr.setTerminal_code(rs.getString(2));
				notice_qr.setYard_code(rs.getString(3));
				notice_qr.setState(rs.getString(4));
				notice_qr.setTime(rs.getString(5));
				list.add(notice_qr);
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return list;
		
	}
	public notice_qr notice_qr_now () throws NamingException, SQLException{
		connect();
		String SQL = "select * from notice_qr where newst ='1'";
		System.out.println(SQL);
		
		notice_qr notice_qr = new notice_qr();
		
		try {		
			pstmt = conn.prepareStatement(SQL);
			rs=pstmt.executeQuery();
			
			while(rs.next()) {
				
				notice_qr.setContainer_code(rs.getString(1));
				notice_qr.setTerminal_code(rs.getString(2));
				notice_qr.setYard_code(rs.getString(3));
				notice_qr.setState(rs.getString(4));
				notice_qr.setTime(rs.getString(5));
				
			}
		}catch(Exception e) {
			System.out.println(e);
		}		
		return notice_qr;
		
	}
	public String notice_qr_now_container_weight (String code) throws NamingException, SQLException{
		connect();
		String SQL = "SELECT no.container_code, con.weight FROM notice_qr AS no JOIN container AS con ON no.container_code = con.cnt_code where container_code = '"+code+"'";
		System.out.println(SQL);
		String weight ="";
		
		notice_qr notice_qr = new notice_qr();
		
		try {		
			pstmt = conn.prepareStatement(SQL);
			rs=pstmt.executeQuery();
			
			if(rs.next()) {
				weight = rs.getString(2);
			}	
		}catch(Exception e) {
			System.out.println(e);
		}		
		return weight;
		
	}
	public String notice_qr_now_weight (String code) throws NamingException, SQLException{
		connect();
		String SQL = "select * from notice_qr where newst ='1'";
		System.out.println(SQL);
		String weight ="";

		try {		
			pstmt = conn.prepareStatement(SQL);
			rs=pstmt.executeQuery();
			
			if(rs.next()) {
				weight= rs.getString(6);
			}	
		}catch(Exception e) {
			System.out.println(e);
		}		
		return weight;
		
	}

	
}
