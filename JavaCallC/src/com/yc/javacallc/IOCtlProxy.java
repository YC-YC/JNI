/**
 * 
 */
package com.yc.javacallc;

/**
 * @author YC
 * @time 2016-6-4 下午6:26:45
 * IOCtl代理
 */
public class IOCtlProxy {

	public int IOCtl(String path, int type, int val)
	{
		if (path == null){
			return -1;
		}
		return Connection.IOCtl(path, type, val);
	}
	
}
