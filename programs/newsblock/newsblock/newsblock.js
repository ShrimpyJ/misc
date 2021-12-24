
async function clearVideos(){
	var resultVideochannelLinks = document.querySelectorAll('ytd-video-renderer a.yt-formatted-string.yt-simple-endpoint, yt-formatted-string.ytd-channel-name');
	console.log(resultVideochannelLinks.length);
	for (var i = 0; i < resultVideochannelLinks.length; i++){
		var n = resultVideochannelLinks[i];
		
		var txt = n.getAttribute('href') || n.getAttribute('title');
		var found = txt ? txt.replace('/user/', '').replace('/channel/', '').toLowerCase() : -1;
		if (found && channels.indexOf(found) > -1){
			console.log("Removing " + found);
			var parent = n.closest("ytd-video-renderer, ytd-compact-video-renderer")
			if (parent) parent.remove();
		}
	}
	const sleep = ms => new Promise(res => setTimeout(res, ms));
	await sleep(2000);
	return clearVideos();
}

for (var i = 0; i < channels.length; i++) channels[i] = channels[i].toLowerCase();
clearVideos();