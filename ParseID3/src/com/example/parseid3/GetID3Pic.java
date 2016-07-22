/**
 * 
 */
package com.example.parseid3;

import com.zhonghong.utils.ID3Jni;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaMetadataRetriever;
import android.util.Log;

/**
 * @author YC
 * @time 2016-7-19 下午2:51:51
 * TODO:获取ID3专辑封面信息
 */
public class GetID3Pic {

	private static final String TAG = "GetID3Pic";
	private MediaMetadataRetriever mRetriever;
	private String cachePath;
	private Bitmap cacheBitmap;
	
	public Bitmap getID3Pic(String path){
		
//		if (mRetriever == null){
//			mRetriever = new MediaMetadataRetriever();
//		}
		
		if (path.equals(cachePath) && cacheBitmap != null){
			Log.i(TAG, "is Same");
			return cacheBitmap;
		}
		cachePath = path;
		byte[] pic = ID3Jni.parseID3Pic(cachePath);
		if (pic != null){
			cacheBitmap = BitmapFactory.decodeByteArray(pic, 0, pic.length);
		}
		else{
			cacheBitmap = null;
		}
//		mRetriever.setDataSource(path);
//		byte[] picture = mRetriever.getEmbeddedPicture();
//		cacheBitmap = BitmapFactory.decodeByteArray(picture, 0, picture.length);
		return cacheBitmap;
	}
	
}
