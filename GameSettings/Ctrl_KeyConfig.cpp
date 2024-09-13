//=================================================================================================
//
//	キーコンフィグ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Ctrl_KeyConfig.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const Array < String > Ctrl_KeyConfig::keynames =
	{
		U"↑",
		U"↓",
		U"←",
		U"→",
		U"ボタン1",
		U"ボタン2",
		U"ボタン3",
		U"ボタン4",
		U"ボタン5",
		U"ボタン6",
		U"ボタン7",
		U"ボタン8",
	};

	const uint32 Ctrl_KeyConfig::NUM_STG = 24;
	const uint32 Ctrl_KeyConfig::NUM_ROW = 12;
	const uint32 Ctrl_KeyConfig::NUM_CLM = 2;

	const char32_t * Ctrl_KeyConfig::FILE_NAME = U"keyconfig.dat";



	Ctrl_KeyConfig::Ctrl_KeyConfig ()
	{
		//初期化
		device_inputs.clear();
		di_strs.clear ();

		for ( int i = 0; i < NUM_STG; ++ i )
		{
			device_inputs.push_back ( DeviceInput () );
			di_strs.push_back ( U"-" );
		}
	}

	Ctrl_KeyConfig::~Ctrl_KeyConfig ()
	{
	}


	void Ctrl_KeyConfig::Load ()
	{
		//デフォルトファイルが存在するかどうか
		if ( FileSystem::Exists ( FILE_NAME ) )
		{
			Load ( s3d::FilePath ( FILE_NAME ) );
			strDiag.assign (U"読み込みました.");
		}
		else
		{
			Init ();
			strDiag.assign (U"対象が読み込めないため初期値で開始しました.");
		}

		//文字列に反映
		for ( int i = 0; i < NUM_STG; ++ i )
		{
			di_strs [i].assign ( DeviceInput_ToString ( device_inputs [ i ] ) ) ;
		}

		//カレントディレクトリの取得
		wchar_t CRNT [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, CRNT );
		s3d::String crnt_path = Unicode::FromWstring ( CRNT );

		crnt_path.append ( U"\\" ) += FILE_NAME;
		filePath.assign ( crnt_path );

	}


	void Ctrl_KeyConfig::Init ()
	{
		device_inputs [ 0 ].SetKeyboard ( SIK_UP );
		device_inputs [ 1 ].SetKeyboard ( SIK_DOWN );
		device_inputs [ 2 ].SetKeyboard ( SIK_LEFT );
		device_inputs [ 3 ].SetKeyboard ( SIK_RIGHT );
		device_inputs [ 4 ].SetKeyboard ( SIK_Z );
		device_inputs [ 5 ].SetKeyboard ( SIK_X );
		device_inputs [ 6 ].SetKeyboard ( SIK_C );
		device_inputs [ 7 ].SetKeyboard ( SIK_V );
		device_inputs [ 8 ].SetKeyboard ( SIK_B );
		device_inputs [ 9 ].SetKeyboard ( SIK_N );
		device_inputs [ 10 ].SetKeyboard ( SIK_M );
		device_inputs [ 11 ].SetKeyboard ( SIK_COMMA );
		device_inputs [ 12 ].SetKeyboard ( SIK_HOME );
		device_inputs [ 13 ].SetKeyboard ( SIK_END );
		device_inputs [ 14 ].SetKeyboard ( SIK_DELETE );
		device_inputs [ 15 ].SetKeyboard ( SIK_PAGEDN );
		device_inputs [ 16 ].SetKeyboard ( SIK_A );
		device_inputs [ 17 ].SetKeyboard ( SIK_S );
		device_inputs [ 18 ].SetKeyboard ( SIK_D );
		device_inputs [ 19 ].SetKeyboard ( SIK_F );
		device_inputs [ 20 ].SetKeyboard ( SIK_G );
		device_inputs [ 21 ].SetKeyboard ( SIK_H );
		device_inputs [ 22 ].SetKeyboard ( SIK_J );
		device_inputs [ 23 ].SetKeyboard ( SIK_K );
	}


	void Ctrl_KeyConfig::Move ()
	{

		//入力の取得
		DeviceInput di = SivInput::Inst()->PushInput ();
		INPUT_DEVICE_TYPE idt = di.GetType();

		//入力が有効な場合
		if ( idt != NODEVICE )
		{
			//保存
			device_inputs [ selected_index ] = di;
			di_strs [ selected_index ] = DeviceInput_ToString ( di );

			//選択を次へ
			selected_index ++;
			if ( selected_index >= NUM_STG ) { selected_index = 0; }
		}

		//保存ボタン
		if ( s3d::SimpleGUI::Button ( U"保存", s3d::Vec2 ( 80, 400 ) ) )
		{
			//固定ディレクトリ
			Save ( s3d::FilePath ( FILE_NAME ) );
#if 0

			//指定ディレクトリ
			wchar_t CRNT [ MAX_PATH ];
			::GetCurrentDirectory ( MAX_PATH, CRNT );
			s3d::String crnt_path = Unicode::FromWstring ( CRNT );

			s3d::Optional < FilePath > path =
				s3d::Dialog::SaveFile (
					{ s3d::FileFilter::AllFiles() }
					, s3d::FilePathView ( crnt_path += U"\\keyconfig.dat" )
					//					, s3d::FilePathView ( U"D:\\Game\\" )
				);

			if ( path )
			{
				Save ( path );
			}

#endif // 0
		}

		//読込ボタン
		if ( s3d::SimpleGUI::Button ( U"読込", s3d::Vec2 ( 200, 400 ) ) )
		{
			//固定ディレクトリ
			Load ( s3d::FilePath ( FILE_NAME ) );
#if 0
			s3d::Optional < FilePath > path = s3d::Dialog::OpenFile ( { s3d::FileFilter::AllFiles() } );
			ctrl_KeyConfig.Load ( path );
#endif // 0
		}
	}


	void Ctrl_KeyConfig::Draw ()
	{
		//プレイヤーの表示
		font ( U"プレイヤー1" ).draw ( 20, 0 );
		font ( U"プレイヤー2" ).draw ( 420, 0 );


		//選択位置の表示
		int x = 0;
		int y = 0;
		if ( selected_index < NUM_ROW )
		{
			x = 20;
			y = 35 + (int)selected_index * 20;
		}
		else
		{
			x = 420;
			y = 35 + ( (int)selected_index - NUM_ROW ) * 20;
		}
		Rect { x, y, 300, 20 }.draw ( ColorF { 0.2, 0.2, 0.2 } );


		//キー名
		//入力種類の表示
		
		for ( size_t i = 0; i < NUM_STG; ++ i )
		{
			String str = U"";

			double dx = 0;
			double dy = 0;
			if ( i < NUM_ROW )
			{
				str = keynames [ i ];
				dx = 20;
				dy = 30 + 20 * (double)i;
			}
			else
			{
				str = keynames [ i - NUM_ROW ];
				dx = 420;
				dy = 30 + 20 * (double)(i - NUM_ROW);
			}

			font ( str ).draw ( dx, dy );
			font ( di_strs [ i ] ).draw ( dx + 200, dy );
			
		}


		//保存ファイル
		//指定なしのときはデフォルト(カレントディレクトリ＋"keyconfig.dat")

		font ( filePath ).draw ( 20, 500 );
		font ( strDiag ).draw ( 20, 520 );
	}


	s3d::String Ctrl_KeyConfig::GamePadInput_ToString ( GamePadInput gpi )
	{
		PAD_INPUT_TYPE pit = gpi.GetInputType ();

		s3d::String str = U"P{}_"_fmt ( gpi.GetID () );

		switch ( pit )
		{
		case PIT_AXIS:			str += U"AXIS_";		break;
		case PIT_POINT_OF_VIEW:	str += U"POV_";		break;

		case PIT_BUTTON:
			str += U"BTN_";
			str += U"{}"_fmt ( gpi.GetButtonID() );
			break;

		case PIT_NO_DATA:		str += U"NO_DATA";	break;
		default:break;
		}
		return str;
	}

	s3d::String Ctrl_KeyConfig::DeviceInput_ToString ( DeviceInput di )
	{
		INPUT_DEVICE_TYPE idt = di.GetType ();

		s3d::String str;
		switch ( idt )
		{
		case KEYBOARD:	str = U"Key_{}"_fmt( di.GetKeyName () );		break;
		case GAMEPAD:	str = GamePadInput_ToString ( di.GetPad() );	break;
		case MOUSE:		str = Unicode::Widen ( STR(MOUSE) );	break;
		default:break;
		}

		return str;
	}



	void Ctrl_KeyConfig::Save ( s3d::Optional < FilePath > path )
	{
		s3d::BinaryWriter bw ( path.value() );

		for ( size_t i = 0; i < NUM_STG; ++ i )
		{
			DeviceInput di = device_inputs [ i ];
			bw.write ( (uint8)di.GetType () );
			bw.write ( (uint8)( di.GetPad ().GetID() ) );
			bw.write ( (uint8)( di.GetPad ().GetInputType() ) );
			bw.write ( (uint8)( di.GetPad ().GetButtonID() ) );
			bw.write ( (uint8)( di.GetPad ().GetLever() ) );
			bw.write ( (uint8)di.GetKey () );
		}

		strDiag.assign(U"保存しました.");
	}

	void Ctrl_KeyConfig::Load ( s3d::Optional < FilePath > path )
	{
		s3d::BinaryReader br ( path.value() );

		for ( size_t i = 0; i < NUM_STG; ++ i )
		{
			uint8 device_type = 0;
			br.read ( device_type );

			uint8 pad_id = 0;
			br.read ( pad_id );

			uint8 input_type = 0;
			br.read ( input_type );

			uint8 btn = 0;
			br.read ( btn );

			uint8 lever = 0;
			br.read ( lever );

			uint8 key = 0;
			br.read ( key );


			INPUT_DEVICE_TYPE idt = (INPUT_DEVICE_TYPE)device_type;
			GamePadInput gpi;
			switch ( idt )
			{
			case KEYBOARD:
				device_inputs [ i ].SetKeyboard ( (KEY_NAME)key );
			break;

			case GAMEPAD:
				gpi.Set ( pad_id, (PAD_INPUT_TYPE)input_type, btn, (LEVER_DIR)lever );
				device_inputs [ i ].SetPad ( gpi );
			break;

			default:break;
			}
		}
	}


}	//namespace GAME

