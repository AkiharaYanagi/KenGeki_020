# ���{��UI
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Japanese.nlf"

# �A�v���P�[�V������
Name "�����N���X�]�[�� �C���p�b�` ver0.11"

#�쐬�����C���X�g�[��
OutFile "Installer.exe"

#�C���X�g�[�������f�B���N�g��
InstallDir "C:\Game\�����N���X�]�[��"

#�y�[�W
Page directory
Page instfiles



#�f�t�H���g�Z�N�V����
Section

	#�o�͐���w�肵�܂��B
	SetOutPath "$INSTDIR"

	#�C���X�g�[�������t�@�C��
	File "F:\Projects\KenGeki_020\KenGeki_020\App\�����J�p�@�C���_�E�ύX�_.txt"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\Readme_�����N���X�]�[��.txt"


	#�o�͐���w�肵�܂��B
	SetOutPath "$INSTDIR\KenGeki"

	#�C���X�g�[�������t�@�C��
	File "F:\Projects\KenGeki_020\KenGeki_020\App\KenGeki_CrossZone.exe"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\chara_Sae_Bin.dat"
	File "F:\Projects\KenGeki_020\KenGeki_020\App\chara_Retsudou_Bin.dat"

SectionEnd
