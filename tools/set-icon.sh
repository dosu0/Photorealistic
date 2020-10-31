# macOS only
sips -i graphics/logo.psd
/usr/bin/DeRez -only icns graphics/logo.psd > tmpicns.rsrc
/usr/bin/Rez -append tmpicns.rsrc -o Photorealistic
/usr/bin/SetFile -a C Photorealistic
rm tmpicns.rsrc