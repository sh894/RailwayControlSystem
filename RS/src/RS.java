import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Image;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.table.AbstractTableModel;


public class RS {
	JFrame J = new JFrame("ע�������");
	JPanel ptable1,ptable2,ptable,ptext,pic;
	JLabel ltable1,ltable2,lpic;
	JTextArea getmassage;
	ImageIcon background;
	Vector vect1,vect2;	    //������������ 
	JScrollPane jsp1,jsp2;	//���������ܶ��� 
	AbstractTableModel tm1,tm2;
	JTable jg_table1,jg_table2;
	String[] title1={"������","�����","IP��ַ","�Ѿ�ע��"};
	String[] title2={"�����","������ʶ","��������","����λ��"};
	ServerSocket ss;
	Socket socket;	//���Ӷ˿�
	String ip;      //�ͻ���ip��ַ
	int port = 6000;
	BufferedInputStream in;		//������
	BufferedOutputStream out;	//�����
	public RS()
	{
		ptable1 = new JPanel();
		ptable2 = new JPanel();
		ptable = new JPanel();
		ptext = new JPanel();
		getmassage= new JTextArea(30,15);
		getmassage.setEditable(false);
		ltable1 = new JLabel("������");
		ltable2 = new JLabel("�����");
		background = new ImageIcon("");
		lpic = new JLabel(background);
		lpic.setBounds(0, 0, background.getIconWidth(),background.getIconHeight());
		pic = (JPanel) J.getContentPane();
		pic.setOpaque(false);
		J.getLayeredPane().add(lpic, new Integer(Integer.MIN_VALUE));
		
		ltable1.setOpaque(false);
		ltable2.setOpaque(false);
		ptable1.setOpaque(false);
		ptable2.setOpaque(false);
		ptable.setOpaque(false);
		ptext.setOpaque(false);
		getmassage.setOpaque(false);
		
		ptable.setLayout(new BoxLayout(ptable,BoxLayout.Y_AXIS));
		ptable.add(ptable1);
		ptable.add(ptable2);
		ptext.add(getmassage);
		
		J.add(ptext,BorderLayout.EAST);
		J.add(ptable,BorderLayout.WEST);
		J.setVisible(true);
		J.setBounds(100, 50, 700, 500);
		J.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

//********************************���ñ��**************************************************
		vect1 = new Vector();								//ʵ�������� 
		tm1 = new AbstractTableModel(){
			public int getColumnCount(){
				return title1.length;
			}														//ȡ�ñ������ 
			public int getRowCount(){ 
				return vect1.size();
			}														//ȡ�ñ������ 
			public Object getValueAt(int row,int column){ 
				if(!vect1.isEmpty()) return ((Vector)vect1.elementAt(row)).elementAt(column); 
				else return null;
			}														//ȡ�õ�Ԫ���е�����ֵ 			
			public String getColumnName(int column){ 
				return title1[column];
			}														//���ñ������ 			
			public void setValueAt(Object value,int row,int column){}	
			public boolean isCellEditable(int row,int column){ 
				return false;
			}//���õ�Ԫ��ɱ༭��Ϊȱʡʵ�� 
		}; 
		jg_table1= new JTable(tm1);							//�����Լ�������ģ�� 
		jg_table1.setToolTipText("��ʾȫ����ѯ���");		//���ð�����ʾ 
		jg_table1.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);//���ñ������ߴ�ģʽ 
		jg_table1.setCellSelectionEnabled(false);			//���õ�Ԫ��ѡ��ʽ 
		jg_table1.setShowVerticalLines(true);				//�����Ƿ���ʾ��Ԫ���ķָ��� 
		jg_table1.setShowHorizontalLines(true); 
		jg_table1.setVisible(true);
		jsp1 = new JScrollPane(jg_table1);//�������Ϲ����� 
		jsp1.setPreferredSize(new Dimension(300,220));
		jsp1.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		jsp1.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		ptable1.add(ltable1,BorderLayout.NORTH);
		ptable1.add(jsp1,BorderLayout.SOUTH);
		
		vect2 = new Vector();								//ʵ�������� 
		tm2 = new AbstractTableModel(){
			public int getColumnCount(){
				return title2.length;
			}														//ȡ�ñ������ 
			public int getRowCount(){ 
				return vect2.size();
			}														//ȡ�ñ������ 
			public Object getValueAt(int row,int column){ 
				if(!vect2.isEmpty()) return ((Vector)vect2.elementAt(row)).elementAt(column); 
				else return null;
			}														//ȡ�õ�Ԫ���е�����ֵ 			
			public String getColumnName(int column){ 
				return title2[column];
			}														//���ñ������ 			
			public void setValueAt(Object value,int row,int column){}			
			public Class getColumnClass(int c){ 
				return getValueAt(0,c).getClass(); 
			}														//ȡ�������������� 				
			public boolean isCellEditable(int row,int column){ 
				return false;
			}//���õ�Ԫ��ɱ༭��Ϊȱʡʵ�� 
		}; 
		jg_table2= new JTable(tm2);							//�����Լ�������ģ�� 
		jg_table2.setToolTipText("��ʾȫ����ѯ���");		//���ð�����ʾ 
		jg_table2.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);//���ñ������ߴ�ģʽ 
		jg_table2.setCellSelectionEnabled(false);			//���õ�Ԫ��ѡ��ʽ 
		jg_table2.setShowVerticalLines(true);				//�����Ƿ���ʾ��Ԫ���ķָ��� 
		jg_table2.setShowHorizontalLines(true); 
		jg_table2.setVisible(true);
		jsp2= new JScrollPane(jg_table2);//�������Ϲ����� 
		jsp2.setPreferredSize(new Dimension(300,200));
		jsp2.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		jsp2.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		ptable2.add(ltable2,BorderLayout.NORTH);
		ptable2.add(jsp2,BorderLayout.SOUTH);
		
		
		
		
//***********************************************��ʼ�����********************************************************		
		try {
			ResultSet rs  = search_rs("select * from Locomt ");
			vect1.removeAllElements();	
			while(rs.next())
			{
				Vector rec_vector=new Vector();							
				//�ӽ������ȡ���ݷ�������rec_vector�� 
				rec_vector.addElement(rs.getString("LocoID")); 
				rec_vector.addElement(rs.getString("GroupID")); 
				rec_vector.addElement(rs.getString("IP")); 
				rec_vector.addElement(rs.getString("login")); 
				vect1.addElement(rec_vector);//����rec_vector��������vect�� 					
			}
			tm1.fireTableStructureChanged();		
			rs.close();	
		}catch (Exception ex){
			ex.printStackTrace();
		}
		
		try {
			ResultSet rs  = search_rs("select * from LocoGroup");
			vect2.removeAllElements();	
			while(rs.next())
			{
				Vector rec_vector=new Vector();							
				//�ӽ������ȡ���ݷ�������rec_vector�� 
				rec_vector.addElement(rs.getString("GroupID")); 
				rec_vector.addElement(rs.getString("Master")); 
				rec_vector.addElement(rs.getString("LocoNum")); 
				rec_vector.addElement(rs.getString("Location"));
				vect2.addElement(rec_vector);//����rec_vector��������vect�� 					
			}
			tm2.fireTableStructureChanged();		
			rs.close();	
		}catch (Exception ex) {
			ex.printStackTrace();
		}
		
//***************************ʱ��********************************************************************
		Date now = new Date();
		DateFormat d1 = DateFormat.getDateInstance(); 
		DateFormat d2 = DateFormat.getTimeInstance(); 
		String d= d1.format(now)+" "+d2.format(now);
		getmassage.setText(getmassage.getText()+d+"ע��������Ѿ�����!\n");
		
		
//*************************************�������Ӷ�ȡ֡*************************************************
		try{	
			ss=new ServerSocket(6000); 
			byte[] buf = new byte[1024];			
			while(true) 
			{   				
				socket = ss.accept(); 
				String RemoteIP = socket.getInetAddress().getHostAddress(); 
				String RemotePort = ":"+socket.getLocalPort(); 			
				in = new BufferedInputStream(socket.getInputStream());
				byte buf1=(byte) in.read(); 
				byte buf2=(byte) in.read();
				byte buf3=(byte) in.read();
				byte buf4=(byte) in.read();
				byte buf5=(byte) in.read();
				
				if (buf1==0x10)
				{
					if(buf2 ==0x02)
					{
						
						DataFrame frame = new DataFrame(buf5);
						switch(buf5)
						{
//*********************************************����ע��֡����***************************************
						case 0x01:     
							frame.length = 27; 
							byte buf6 = (byte) in.read(); //���ػ�����
							int masterid=1;
							switch((int) buf6)
							{
								case 1:masterid = 4043;break;
								case 2:masterid = 4012;break;
								case 3:masterid = 4013;break;
								case 4:masterid = 4033;break;
							}
							in.read();
							byte buf7 = (byte) in.read(); //��������
							int localid=1;
							switch((int) buf7)
							{
								case 1:localid = 4043;break;
								case 2:localid = 4012;break;
								case 3:localid = 4013;break;
								case 4:localid = 4033;break;
							}
							in.read();
							byte buf8 = (byte) in.read(); //�ӳ�������
							int slaveid1=2;
							switch((int) buf8)
							{
								case 1:slaveid1 = 4043;break;
								case 2:slaveid1 = 4012;break;
								case 3:slaveid1 = 4013;break;
								case 4:slaveid1 = 4033;break;
							}
							in.read();
							byte buf9 = (byte) in.read();
							int slaveid2=3;
							switch((int) buf9)
							{
								case 1:slaveid2 = 4043;break;
								case 2:slaveid2 = 4012;break;
								case 3:slaveid2 = 4013;break;
								case 4:slaveid2 = 4033;break;
							}
							in.read();
							byte buf20 = (byte)in.read();
							int slaveid3=4;
							switch((int) buf20)
							{
								case 1:slaveid3 = 4043;break;
								case 2:slaveid3 = 4012;break;
								case 3:slaveid3 = 4013;break;
								case 4:slaveid3 = 4033;break;
							}	
							DateFormat d3 = DateFormat.getDateInstance(); 
							DateFormat d4 = DateFormat.getTimeInstance(); 
							String d5= d3.format(now)+" "+d4.format(now);
							getmassage.setText(getmassage.getText()+d5+"��������ע��!������:"+masterid+"������:"+localid+"\n");
	/////////////////						//���±�
							try
							{
								search_void("insert into LocoGroup values('"+masterid+"','"+localid+"','4','��')");				        
								search_void("insert Locomt values('0"+localid+"','"+masterid+"',' ',' ')");							
								search_void("insert Locomt values('0"+slaveid1+"','"+masterid+"',' ',' ')");
								search_void("insert Locomt values('0"+slaveid2+"','"+masterid+"',' ',' ')");							
								search_void("insert Locomt values('0"+slaveid3+"','"+masterid+"',' ',' ')");
								search_void("update Locomt set login ='1' where LocoID='0"+localid+"'");
								ResultSet res1  = search_rs("select * from Locomt");
								ResultSet res2 = search_rs("select * from LocoGroup");
								vect1.removeAllElements();	
								while(res1.next())
								{
									Vector rec_vector=new Vector();							
									//�ӽ������ȡ���ݷ�������rec_vector�� 
									rec_vector.addElement(res1.getString("LocoID")); 
									rec_vector.addElement(res1.getString("GroupID")); 
									rec_vector.addElement(res1.getString("IP")); 
									rec_vector.addElement(res1.getString("login")); 
									vect1.addElement(rec_vector);//����rec_vector��������vect�� 					
								}
								tm1.fireTableStructureChanged();
								res1.close();
								
								vect2.removeAllElements();	
								while(res2.next())
								{
									Vector rec_vector=new Vector();							
									//�ӽ������ȡ���ݷ�������rec_vector�� 
									rec_vector.addElement(res2.getString("GroupID")); 
									rec_vector.addElement(res2.getString("Master")); 
									rec_vector.addElement(res2.getString("LocoNum")); 
									rec_vector.addElement(res2.getString("Location"));
									vect2.addElement(rec_vector);//����rec_vector��������vect�� 					
								}
								tm2.fireTableStructureChanged();		
								res2.close();
							}catch (Exception e1){
								e1.printStackTrace();
							}	
				
							
							DateFormat d6 = DateFormat.getDateInstance(); 
							DateFormat d7 = DateFormat.getTimeInstance(); 
							String d8= d6.format(now)+" "+d7.format(now);
							getmassage.setText(getmassage.getText()+d8+"����ע��ɹ�!\n");
							
//*******************************************ע��ɹ��ظ�********************************************************				
							DataFrame signsuccess = new DataFrame((byte)0x22);					
							signsuccess.buf[0]=(byte)16;
							signsuccess.buf[1]=(byte)2;
							signsuccess.buf[2]=(byte)34;
							signsuccess.buf[3]=0x00;
							signsuccess.buf[4]=(byte)0x76;
							signsuccess.buf[5]=buf6;
							signsuccess.buf[6]=0;
							signsuccess.buf[7]=buf7;
							signsuccess.buf[8]=0x00;
							signsuccess.buf[9]=(byte)3;
							signsuccess.buf[10]=buf6;
							signsuccess.buf[11]=0x00;
							signsuccess.buf[12]=(byte)10; //��IP
							signsuccess.buf[13]=(byte)10;
							signsuccess.buf[14]=(byte)10;
							signsuccess.buf[15]=(byte)1;
							signsuccess.buf[16]=(byte)02;
							signsuccess.buf[17]=0x00;
							signsuccess.buf[18]=(byte)10; //��1 IP
							signsuccess.buf[19]=(byte)10;
							signsuccess.buf[20]=(byte)10;
							signsuccess.buf[21]=(byte)2;
							signsuccess.buf[22]=(byte)03;
							signsuccess.buf[23]=0x00;                      
							signsuccess.buf[24]=(byte)10; //��2 IP
							signsuccess.buf[25]=(byte)10;
							signsuccess.buf[26]=(byte)10;
							signsuccess.buf[27]=(byte)3;
							signsuccess.buf[28]=(byte)04;
							signsuccess.buf[29]=0x00;
							signsuccess.buf[30]=(byte)10; //��3 IP
							signsuccess.buf[31]=(byte)10;
							signsuccess.buf[32]=(byte)10;
							signsuccess.buf[33]=(byte)4;
							try
							{
								Socket s = new Socket(RemoteIP,port);
								out = new BufferedOutputStream(s.getOutputStream());
								out.write(signsuccess.buf, 0, signsuccess.buf.length);
							}catch(Exception e){
								e.printStackTrace();
							}						
							out.flush();
							break;
							
//*********************************************�ӳ�ע��֡����**************************************************************************	
						case 0x02:                                   
							buf = new byte [9];
							frame.length = 9;
							byte buf10 =(byte) in.read();   //���ػ�����
							int masterid1 =1;
							switch((int) buf10)
							{
								case 1:masterid1 = 4043;break;
								case 2:masterid1 = 4012;break;
								case 3:masterid1 = 4013;break;
								case 4:masterid1 = 4033;break;
							}
							in.read();
							byte buf11 = (byte) in.read();  //��������
							int localid1 =2;
							switch((int) buf11)
							{
								case 1:localid1 = 4043;break;
								case 2:localid1 = 4012;break;
								case 3:localid1 = 4013;break;
								case 4:localid1 = 4033;break;
							}
							DateFormat d9 = DateFormat.getDateInstance(); 
							DateFormat d10 = DateFormat.getTimeInstance(); 
							String d11= d9.format(now)+" "+d10.format(now);
							getmassage.setText(getmassage.getText()+d11+"��������ע��!������:"+masterid1+"������:"+localid1+"\n");
							//���±�
							try
							{
								search_void("update Locomt set GroupID='"+masterid1+"' where LocoID='0"+localid1+"'");
								search_void("update Locomt set login = '1'where LocoID='0"+localid1+"'");
								ResultSet rs = search_rs("select * from Locomt");
								vect1.removeAllElements();	
								while(rs.next())
								{
									Vector rec_vector=new Vector();							
									//�ӽ������ȡ���ݷ�������rec_vector�� 
									rec_vector.addElement(rs.getString("LocoID")); 
									rec_vector.addElement(rs.getString("GroupID")); 
									rec_vector.addElement(rs.getString("IP")); 
									rec_vector.addElement(rs.getString("login")); 
									vect1.addElement(rec_vector);//����rec_vector��������vect�� 					
								}
								tm1.fireTableStructureChanged();
								rs.close();
							}catch (Exception e1){
								e1.printStackTrace();
							}
						
							DateFormat d12 = DateFormat.getDateInstance(); 
							DateFormat d13 = DateFormat.getTimeInstance(); 
							String d14= d12.format(now)+" "+d13.format(now);
							getmassage.setText(getmassage.getText()+d14+"����ע��ɹ�!\n");
							
//*********************************************����ע��ɹ��ظ�**************************************************						
							DataFrame sign1success = new DataFrame((byte)0x22);
							sign1success.buf[0]=(byte)16;
							sign1success.buf[1]=(byte)2;
							sign1success.buf[2]=(byte)34;
							sign1success.buf[3]=0x00;
							sign1success.buf[4]=(byte)0x76;
							sign1success.buf[5]=buf10;
							sign1success.buf[6]=0;
							sign1success.buf[7]=buf11;
							sign1success.buf[8]=0x00;
							sign1success.buf[9]=(byte)3;
							sign1success.buf[10]=buf10;
							sign1success.buf[11]=0x00;
							sign1success.buf[12]=(byte)10;  //��IP
							sign1success.buf[13]=(byte)10;
							sign1success.buf[14]=(byte)10;
							sign1success.buf[15]=(byte)1;
							sign1success.buf[16]=(byte)02;
							sign1success.buf[17]=0x00;
							sign1success.buf[18]=(byte)10;  //��1 IP
							sign1success.buf[19]=(byte)10;
							sign1success.buf[20]=(byte)10;
							sign1success.buf[21]=(byte)2;
							sign1success.buf[22]=(byte)03;
							sign1success.buf[23]=0x00;                      
							sign1success.buf[24]=(byte)10;   //��2 IP
							sign1success.buf[25]=(byte)10;
							sign1success.buf[26]=(byte)10;
							sign1success.buf[27]=(byte)3;
							sign1success.buf[28]=(byte)04;
							sign1success.buf[29]=0x00;
							sign1success.buf[30]=(byte)10;   //��3 IP
							sign1success.buf[31]=(byte)10;
							sign1success.buf[32]=(byte)10;
							sign1success.buf[33]=(byte)4;
							try{
								Socket s = new Socket(RemoteIP,port);
								out = new BufferedOutputStream(s.getOutputStream());
								out.write(sign1success.buf, 0, sign1success.buf.length);
							}catch(Exception e){
								e.printStackTrace();
							}						
							out.flush();
							break;
							
//*************************************����ע������***********************************************************************
						case 0x12:                                  
							buf = new byte [9];
							frame.length = 9;
							byte buf12 = (byte) in.read();       //���ػ�����
							int masterid2=1;
							switch((int) buf12)
							{
								case 1:masterid2 = 4043;break;
								case 2:masterid2 = 4012;break;
								case 3:masterid2 = 4013;break;
								case 4:masterid2 = 4033;break;
								default:masterid2 =4043;
							}
							in.read();
							byte buf13 = (byte) in.read();      //��������
							int localid2 = 2;
							System.out.print(buf13);
							switch((int) buf13)
							{
								case 1:localid2 = 4043;break;
								case 2:localid2 = 4012;break;
								case 3:localid2 = 4013;break;
								case 4:localid2 = 4033;break;
								default:localid2 =4043;
							}
							DateFormat d15 = DateFormat.getDateInstance(); 
							DateFormat d16 = DateFormat.getTimeInstance(); 
							String d17= d15.format(now)+" "+d16.format(now);
							getmassage.setText(getmassage.getText()+d17+"�����������ע��!������:"+masterid2+"������:"+localid2+"\n");
							//���±�
							try{	System.out.print(masterid2);
							System.out.println();
							        System.out.print(localid2+' ');
							        System.out.println();
							        
							        
           ///////////////////////////						        
									if(masterid2==localid2)
									{
										System.out.print(masterid2+' ');
										System.out.println();
										search_void("delete from Locomt    where GroupID='"+masterid2+"'");
								        search_void("delete from LocoGroup where GroupID='"+masterid2+"'");
								    }
								     else
									{   
								    	 search_void("update Locomt set login=NULL where LocoID='0"+localid2+"'");
									}
								ResultSet res1 = search_rs("select * from Locomt");
								ResultSet res2 = search_rs("select * from LocoGroup");
								vect1.removeAllElements();	
								while(res1.next())
								{
									Vector rec_vector=new Vector();							
									//�ӽ������ȡ���ݷ�������rec_vector�� 
									rec_vector.addElement(res1.getString("LocoID")); 
									rec_vector.addElement(res1.getString("GroupID")); 
									rec_vector.addElement(res1.getString("IP")); 
									rec_vector.addElement(res1.getString("login")); 
									vect1.addElement(rec_vector);//����rec_vector��������vect�� 					
								}
								tm1.fireTableStructureChanged();
								res1.close();
								vect2.removeAllElements();	
								while(res2.next())
								{
									Vector rec_vector=new Vector();							
									//�ӽ������ȡ���ݷ�������rec_vector�� 
									rec_vector.addElement(res2.getString("GroupID")); 
									rec_vector.addElement(res2.getString("Master")); 
									rec_vector.addElement(res2.getString("LocoNum")); 
									rec_vector.addElement(res2.getString("Location"));
									vect2.addElement(rec_vector);//����rec_vector��������vect�� 					
								}
								tm2.fireTableStructureChanged();		
								res2.close();
							}catch (Exception e1)
							{
								e1.printStackTrace();
								
//**************************************����ע��ʧ�ܻظ�***************************************************************************
								DataFrame cancelfail = new DataFrame((byte)0x92);
								cancelfail.length=10;
								cancelfail.buf[0]=0x10;
								cancelfail.buf[1]=0x02;
								cancelfail.buf[2]=(byte)10;
								cancelfail.buf[3]=0x00;
								cancelfail.buf[4]=(byte)0x42;
								cancelfail.buf[5]=(byte)01;
								cancelfail.buf[6]=0x00;
								cancelfail.buf[7]=buf13;
								cancelfail.buf[8]=0x00;
								cancelfail.buf[9]=0x01;			
								try{
									Socket s = new Socket(RemoteIP,port);
									out = new BufferedOutputStream(s.getOutputStream());
									out.write(cancelfail.buf, 0, cancelfail.length);
								}catch(Exception e){
									e.printStackTrace();
								}
								out.flush();
								String d20 = (new SimpleDateFormat("yyyy-MM-dd hh:mm:ss")).format(new Date());
								getmassage.setText(getmassage.getText()+d20+"ע��ʧ�ܻظ��Ѿ�����!\n");
								break;
							}
							
							DateFormat d18 = DateFormat.getDateInstance(); 
							DateFormat d19 = DateFormat.getTimeInstance(); 
							String d20= d18.format(now)+" "+d19.format(now);
							getmassage.setText(getmassage.getText()+d20+"��������ע���ɹ�!\n");
							
//***************************************����ע���ɹ��ظ�****************************************************************************						
							DataFrame cancelsuccess = new DataFrame((byte)0x92);
							cancelsuccess.buf[0]=(byte)0x10;
							cancelsuccess.buf[1]=(byte)2;
							cancelsuccess.buf[2]=(byte)10;
							cancelsuccess.buf[3]=(byte)0x00;
							cancelsuccess.buf[4]=(byte)0x42;
							cancelsuccess.buf[5]=(byte)01;
							cancelsuccess.buf[6]=0x00;
							cancelsuccess.buf[7]=buf13;
							cancelsuccess.buf[8]=0x00;
							cancelsuccess.buf[9]=0x00;				
							try{	
								Socket s = new Socket(RemoteIP,port);
								out = new BufferedOutputStream(s.getOutputStream());
								out.write(cancelsuccess.buf, 0, cancelsuccess.buf.length);
							}catch(Exception e){
								e.printStackTrace();
							}						
							out.flush();
							DateFormat d21 = DateFormat.getDateInstance(); 
							DateFormat d22 = DateFormat.getTimeInstance(); 
							String d23= d21.format(now)+" "+d22.format(now);
							getmassage.setText(getmassage.getText()+d23+"ע���ɹ��ظ��Ѿ�����!\n");
							break;
							
						default: break;
						}
					}
				}
				out.close(); 
				in.close(); 
				socket.close();
			}
		}
		catch (IOException e){
			e.printStackTrace();
		}
	}
	
	
	
	void search_void(String sql){
		try{
			Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
			Connection conn = DriverManager.getConnection("jdbc:sqlserver://localhost:1433;DatabaseName=����ͬ��ϵͳ","sa", "123");
			Statement stmt = conn.createStatement();
			stmt.executeUpdate(sql);
		}catch (Exception e){
			e.printStackTrace();
		}
	}
	ResultSet search_rs(String sql){
		try{
			Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
			Connection conn = DriverManager.getConnection("jdbc:sqlserver://localhost:1433;DatabaseName=����ͬ��ϵͳ","sa", "123");
			Statement stmt = conn.createStatement();
			return stmt.executeQuery(sql);
		}catch (Exception e){
			e.printStackTrace();
			return null;
		}
	}
	public static void main(String[] args) {
		new RS();
	}
	
}