package seaitc;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.naming.NamingException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet implementation class control
 */
@WebServlet("*.do")
public class control extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public control() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		request.setCharacterEncoding("UTF-8");		
		
		doProcess(request,response);
	
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		request.setCharacterEncoding("UTF-8");		
		
		doProcess(request,response);
	}
	public void doProcess(HttpServletRequest request, HttpServletResponse response) 
	throws ServletException, IOException {
	
		HttpSession session = request.getSession();
		String requestURI = request.getRequestURI();
		int cmdIdx = requestURI.lastIndexOf("/")+1;
		
		String command = requestURI.substring(cmdIdx);
		//System.out.println("aa");
		
		String viewPage = null;
		
		// URI, command 확인
		//System.out.println("requestURI : "+requestURI);
		//System.out.println("command : "+command);
		
	
		if(command.equals("login.do")) {
			String id = request.getParameter("id");
			String pw = request.getParameter("pw");
			
			User user = new User();
			DAO dao = new DAO();
			
			try {
				user = dao.login(id, pw);
				System.out.println(user.id);
				System.out.println(user.pw);
				if(user.getId() != null)
				{
					session.setAttribute("id", id);
					request.setAttribute("id2", user.id);
					request.setAttribute("pw", user.pw);
					request.setAttribute("user", user);
					viewPage = "login_result.jsp";
					
				}
				else {
					request.setAttribute("user", 11);
					viewPage = "login_result3.jsp";
				}
			} catch (SQLException | NamingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		  else if(command.equals("yard_connect.do")) { // 터미널 들어감
		         String t_code = request.getParameter("t_code");
		         String working_yard = request.getParameter("working_yard");
		         String state = request.getParameter("state");
		         if (state.equals("jakup")) {
		            state = "작업중";
		         }else {
		            state = "사고발생";
		         }
		         //System.out.println(t_code);  // 터미널 코드 확인 
		         //System.out.println(working_yard);  // 야드 확인
		         
		         DAO dao = new DAO();
		         container container = new container();

		         try {
		            container = dao.yard_container(t_code,working_yard,state);
		            System.out.println(container.getCnt_code());
		            request.setAttribute("container", container);
		         }catch(SQLException | NamingException e) {
		            
		         }

		         viewPage ="yard_connect_json.jsp";
		         
		      }
		      else if(command.equals("terminal_connect.do")) { // 터미널 들어감
		         String t_code = request.getParameter("t_code");
		         System.out.println(t_code);  // 터미널 코드 확인 
		         
		         DAO dao = new DAO();
		         ArrayList<container> container = new ArrayList<container>();
		         ArrayList<ship> ship = new ArrayList<ship>();
		         ArrayList<port_yard> yard = new ArrayList<port_yard>();
		         try {
		            container = dao.container(t_code);
		            ship = dao.ship(t_code);
		            yard = dao.port_yard(t_code);
		         }catch(SQLException | NamingException e) {
		            
		         }
		         request.setAttribute("ship", ship);
		         request.setAttribute("yard", yard);
		         request.setAttribute("container", container);
		         
		         viewPage ="terminal_connect_json.jsp";
		         
		      }
		      else if(command.equals("container_detail.do")) { // 터미널 들어감
		         String t_code = request.getParameter("t_code");
		         String container_code = request.getParameter("container_code");
		         System.out.println(t_code);  // 터미널 코드 확인 
		         
		         DAO dao = new DAO();
		         container container = new container();
		         try {
		            container = dao.container_detail(t_code,container_code);
		            
		         }catch(SQLException | NamingException e) {
		            
		         }
		         System.out.println("컨테이너 상세 검색 sql 갔다옴");
		         request.setAttribute("container", container);
		         System.out.println("container : "+container);
		         viewPage ="container_detail_json.jsp";
		         
		      }
		      else {
		         
		      }      
		      
		      RequestDispatcher dispatcher = request.getRequestDispatcher(viewPage);
		      dispatcher.forward(request, response);
		   }

		}