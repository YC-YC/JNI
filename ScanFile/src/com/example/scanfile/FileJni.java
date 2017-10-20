/**
 * 
 */
package com.example.scanfile;

/**
 * @author YC
 * @time 2017-7-7 下午3:08:59
 * TODO:
 */
public class FileJni {
	
	static { 
		System.loadLibrary("ScanFile");
	}

	 public static native void listImpl(String path);
	 
	 public static native void set(String source, String song, String artist, String album,
 			String albumArt, long duration, long playlistNum, String songId,
 			long mode);
	 
	 
}
