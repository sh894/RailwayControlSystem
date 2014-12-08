
public class DataFrame {
	public char  framehead;
	public byte  frametype;
	public char  framecontent;
	public int   length;
	public byte  []buf; 
	public   DataFrame(byte type)
	{
	
		length = 0;
		frametype = type;
		switch(frametype)
		{
		case 0x01:                                   //主车注册帧
			buf = new byte [27];
			length = 27; 
			break;
		case 0x02:                                   //从车注册帧
			buf = new byte [9];
			length = 9;
			break;
		case 0x12:                                   //机车注销帧
			buf = new byte [9];
			length = 9;
			break;
		case (byte) 0x92:                            //注销回复帧
			buf = new byte [10];
			length = 10;
			break;
		case (byte) 0x81:                            //注册失败回复
			buf = new byte [10];
			length = 10;
			break;
		case 0x22:                                   //注册成功回复
			buf = new byte [34];
			length = 34;
			break;
		default:
			break;		
		}
	}
	public  byte getType()
	{
		return this.frametype;
	}
	public char  getContent()
	{
		return this.framecontent;
	}
	public int  getLength()
	{
		return this.length;
	}
	
}
