/**
 * 
 */
package com.example.scanfile;

/**
 * @author YC
 * @time 2017-7-11 下午3:05:23
 * TODO:
 */
public class MediaInfo {

	private String source ;
	private String song ;
	private String artist ;
	private String album ;
	private String albumArt ;
	private long duration ;
	private long playlistNum ;
	private String songId ;
	private long mode ;
	/**
	 * @param source
	 * @param song
	 * @param artist
	 * @param album
	 * @param albumArt
	 * @param duration
	 * @param playlistNum
	 * @param songId
	 * @param mode
	 */
	public MediaInfo(String source, String song, String artist, String album,
			String albumArt, long duration, long playlistNum, String songId,
			long mode) {
		super();
		this.source = source;
		this.song = song;
		this.artist = artist;
		this.album = album;
		this.albumArt = albumArt;
		this.duration = duration;
		this.playlistNum = playlistNum;
		this.songId = songId;
		this.mode = mode;
	}
	/**
	 * @return the source
	 */
	public String getSource() {
		return source;
	}
	/**
	 * @return the song
	 */
	public String getSong() {
		return song;
	}
	/**
	 * @return the artist
	 */
	public String getArtist() {
		return artist;
	}
	/**
	 * @return the album
	 */
	public String getAlbum() {
		return album;
	}
	/**
	 * @return the albumArt
	 */
	public String getAlbumArt() {
		return albumArt;
	}
	/**
	 * @return the duration
	 */
	public long getDuration() {
		return duration;
	}
	/**
	 * @return the playlistNum
	 */
	public long getPlaylistNum() {
		return playlistNum;
	}
	/**
	 * @return the songId
	 */
	public String getSongId() {
		return songId;
	}
	/**
	 * @return the mode
	 */
	public long getMode() {
		return mode;
	}
	
	
}
