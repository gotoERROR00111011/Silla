package seaitc;

public class ship {
	private String ship_name;
	private String terminal_code;
	private String in_date;
	private String out_date;
	private int max_work;
	private int now_work;
	private int rest_work;
	
	
	public String getShip_name() {
		return ship_name;
	}
	public void setShip_name(String ship_name) {
		this.ship_name = ship_name;
	}
	public String getTerminal_code() {
		return terminal_code;
	}
	public void setTerminal_code(String terminal_code) {
		this.terminal_code = terminal_code;
	}
	public String getIn_date() {
		return in_date;
	}
	public void setIn_date(String in_date) {
		this.in_date = in_date;
	}
	public String getOut_date() {
		return out_date;
	}
	public void setOut_date(String out_date) {
		this.out_date = out_date;
	}
	public int getMax_work() {
		return max_work;
	}
	public void setMax_work(int max_work) {
		this.max_work = max_work;
	}
	public int getNow_work() {
		return now_work;
	}
	public void setNow_work(int now_work) {
		this.now_work = now_work;
	}
	public int getRest_work() {
		return rest_work;
	}
	public void setRest_work(int rest_work) {
		this.rest_work = rest_work;
	}
}
