<module name="crypt32" type="win32dll" baseaddress="${BASEADDRESS_CRYPT32}" installbase="system32" installname="crypt32.dll" allowwarnings="true" crt="msvcrt">
	<importlibrary definition="crypt32.spec" />
	<include base="crypt32">.</include>
	<include base="ReactOS">include/reactos/wine</include>
	<define name="__WINESRC__" />
	<redefine name="_WIN32_WINNT">0x600</redefine>
	<library>wine</library>
	<library>user32</library>
	<library>advapi32</library>
	<library>kernel32</library>
	<library>ntdll</library>
	<library>imagehlp</library>
	<library>pseh</library>
	<file>base64.c</file>
	<file>cert.c</file>
	<file>chain.c</file>
	<file>collectionstore.c</file>
	<file>context.c</file>
	<file>crl.c</file>
	<file>decode.c</file>
	<file>encode.c</file>
	<file>filestore.c</file>
	<file>main.c</file>
	<file>msg.c</file>
	<file>object.c</file>
	<file>oid.c</file>
	<file>proplist.c</file>
	<file>protectdata.c</file>
	<file>provstore.c</file>
	<file>regstore.c</file>
	<file>rootstore.c</file>
	<file>serialize.c</file>
	<file>sip.c</file>
	<file>store.c</file>
	<file>str.c</file>
	<file>ctl.c</file>
	<file>message.c</file>
	<file>crypt32_De.rc</file>
	<file>crypt32_En.rc</file>
	<file>crypt32_Fr.rc</file>
	<file>crypt32_Ko.rc</file>
	<file>crypt32_Nl.rc</file>
	<file>crypt32_No.rc</file>
	<file>crypt32_Pt.rc</file>
	<file>crypt32_Ro.rc</file>
	<file>crypt32_Sv.rc</file>
	<file>version.rc</file>
	<!-- See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38054#c7 -->
	<compilerflag compilerset="gcc">-fno-unit-at-a-time</compilerflag>
</module>
