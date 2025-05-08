//=================================================================================================
//
//	CharaSele_Cursor
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Cursor.h"
#include "../GameMain/SeConst.h"
#include "_CharaSele_Player.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region CONST
	//---------------------------------------------------------
	//カーソル
	//表示位置定数
	static constexpr float	_FACE_X_0 = 410 - 2;
	static constexpr float	_FACE_X_1 = _FACE_X_0 + 150;
	static constexpr float	_FACE_X_2 = _FACE_X_1 + 150;
	static constexpr float	_FACE_Y_0 =  70 - 2;
	static constexpr float	_FACE_Y_1 = _FACE_Y_0 + 150;
	static constexpr float	_FACE_Y_2 = _FACE_Y_0 + 560;
	static constexpr float	_FACE_Y_3 = _FACE_Y_2 + 150;


	//---------------------------------------------------------
	//枠位置定数
	//	キャラID, 名前, セレクト位置x, セレクト位置y, 上移動先, 下移動先, 左移動先, 右移動先

#define GABA	1

#if GABA

	constexpr ChSlct CHSL_POS [ CHARA_SELE_NUM ] = 
	{
{ CHSLID_00, CHARA_OUKA,		_FACE_X_0, _FACE_Y_0, CHSLID_03, CHSLID_03, CHSLID_02, CHSLID_02 }, 
{ CHSLID_01, CHARA_TEST,		_FACE_X_1, _FACE_Y_0, CHSLID_10, CHSLID_04, CHSLID_00, CHSLID_02 }, 
{ CHSLID_02, CHARA_SAE ,		_FACE_X_2, _FACE_Y_0, CHSLID_05, CHSLID_05, CHSLID_00, CHSLID_00 }, 
{ CHSLID_03, CHARA_RETSUDOU,	_FACE_X_0, _FACE_Y_1, CHSLID_00, CHSLID_00, CHSLID_05, CHSLID_05 }, 
{ CHSLID_04, CHARA_TEST,		_FACE_X_1, _FACE_Y_1, CHSLID_01, CHSLID_07, CHSLID_03, CHSLID_05 }, 
{ CHSLID_05, CHARA_GABADARUGA,	_FACE_X_2, _FACE_Y_1, CHSLID_02, CHSLID_02, CHSLID_03, CHSLID_03 },  
{ CHSLID_06, CHARA_TEST,		_FACE_X_0, _FACE_Y_2, CHSLID_03, CHSLID_09, CHSLID_08, CHSLID_07 }, 
{ CHSLID_07, CHARA_TEST,		_FACE_X_1, _FACE_Y_2, CHSLID_04, CHSLID_10, CHSLID_06, CHSLID_08 }, 
{ CHSLID_08, CHARA_TEST,		_FACE_X_2, _FACE_Y_2, CHSLID_05, CHSLID_11, CHSLID_07, CHSLID_06 }, 
{ CHSLID_09, CHARA_TEST,		_FACE_X_0, _FACE_Y_3, CHSLID_06, CHSLID_00, CHSLID_11, CHSLID_10 }, 
{ CHSLID_10, CHARA_TEST,		_FACE_X_1, _FACE_Y_3, CHSLID_07, CHSLID_01, CHSLID_09, CHSLID_11 }, 
{ CHSLID_11, CHARA_TEST,		_FACE_X_2, _FACE_Y_3, CHSLID_08, CHSLID_02, CHSLID_10, CHSLID_09 }, 
	};

#else

	constexpr ChSlct CHSL_POS [ CHARA_SELE_NUM ] = 
	{
{ CHSLID_00, CHARA_OUKA,		_FACE_X_0, _FACE_Y_0, CHSLID_03, CHSLID_03, CHSLID_02, CHSLID_02 }, 
{ CHSLID_01, CHARA_TEST,		_FACE_X_1, _FACE_Y_0, CHSLID_10, CHSLID_04, CHSLID_00, CHSLID_02 }, 
{ CHSLID_02, CHARA_SAE ,		_FACE_X_2, _FACE_Y_0, CHSLID_03, CHSLID_03, CHSLID_00, CHSLID_00 }, 
{ CHSLID_03, CHARA_RETSUDOU,	_FACE_X_0, _FACE_Y_1, CHSLID_00, CHSLID_00, CHSLID_02, CHSLID_02 }, 
{ CHSLID_04, CHARA_TEST,		_FACE_X_1, _FACE_Y_1, CHSLID_01, CHSLID_07, CHSLID_03, CHSLID_05 }, 
{ CHSLID_05, CHARA_GABADARUGA,	_FACE_X_2, _FACE_Y_1, CHSLID_02, CHSLID_02, CHSLID_03, CHSLID_03 },  
{ CHSLID_06, CHARA_TEST,		_FACE_X_0, _FACE_Y_2, CHSLID_03, CHSLID_09, CHSLID_08, CHSLID_07 }, 
{ CHSLID_07, CHARA_TEST,		_FACE_X_1, _FACE_Y_2, CHSLID_04, CHSLID_10, CHSLID_06, CHSLID_08 }, 
{ CHSLID_08, CHARA_TEST,		_FACE_X_2, _FACE_Y_2, CHSLID_05, CHSLID_11, CHSLID_07, CHSLID_06 }, 
{ CHSLID_09, CHARA_TEST,		_FACE_X_0, _FACE_Y_3, CHSLID_06, CHSLID_00, CHSLID_11, CHSLID_10 }, 
{ CHSLID_10, CHARA_TEST,		_FACE_X_1, _FACE_Y_3, CHSLID_07, CHSLID_01, CHSLID_09, CHSLID_11 }, 
{ CHSLID_11, CHARA_TEST,		_FACE_X_2, _FACE_Y_3, CHSLID_08, CHSLID_02, CHSLID_10, CHSLID_09 }, 
	};

#endif // 0


#pragma endregion


	CharaSele_Cursor::CharaSele_Cursor ()
	{
		//カーソル
		m_cursor = std::make_shared < GrpBlink > ();
		m_cursor->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Cursor_1p.png" );
		m_cursor->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Cursor_2p.png" );
		m_cursor->SetTimer ( 15 );
		m_cursor->SetZ ( Z_SYS );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );
	}

	CharaSele_Cursor::~CharaSele_Cursor ()
	{
	}

	void CharaSele_Cursor::PlayerInit ( PLAYER_ID id )
	{
		m_player_id = id;

		if ( PLAYER_ID_1 == id )
		{
			m_chsl_id = CHSLID_00;
			m_cursor->SetPos ( GetPos ( CHSLID_00 ) );
			m_cursor->SetIndexTexture ( 0 );
		}
		else if ( PLAYER_ID_2 == id )
		{
			m_chsl_id = CHSLID_02;
			m_cursor->SetPos ( GetPos ( CHSLID_02 ) );
			m_cursor->SetIndexTexture ( 1 );
		}
	}

	void CharaSele_Cursor::ParamInit ( P_Param p )
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			p->GetCharaName1p ();
			m_chsl_id = CHSLID_00;
			m_cursor->SetPos ( GetPos ( CHSLID_00 ) );
			m_cursor->SetIndexTexture ( 0 );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_chsl_id = CHSLID_02;
			m_cursor->SetPos ( GetPos ( CHSLID_02 ) );
			m_cursor->SetIndexTexture ( 1 );
		}
	}

	void CharaSele_Cursor::SetChara ( CHARA_SELE_ID id )
	{
		m_chsl_id = id;
		m_cursor->SetPos ( GetPos ( m_chsl_id ) );
	}

	CHARA_NAME CharaSele_Cursor::GetCharaName () const
	{
		return CHSL_POS [ m_chsl_id ].Name;
	}


	VEC2 CharaSele_Cursor::GetPos ( CHARA_SELE_ID chsl_id )
	{
		return VEC2 { CHSL_POS [ chsl_id ].x, CHSL_POS [ chsl_id ].y };
	}

	void CharaSele_Cursor::Input ()
	{
		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//移動
		if ( CFG_PUSH_KEY_PL ( id, PLY_UP) ) { Up (); }
		if ( CFG_PUSH_KEY_PL ( id, PLY_DOWN ) ) { Down (); }
		if ( CFG_PUSH_KEY_PL ( id, PLY_LEFT ) ) { Left (); }
		if ( CFG_PUSH_KEY_PL ( id, PLY_RIGHT ) ) { Right (); }
	}


	void CharaSele_Cursor::Up ()
	{
		m_chsl_id = CHSL_POS [ m_chsl_id ].UP;
		Select ();
	}
	void CharaSele_Cursor::Down ()
	{
		m_chsl_id = CHSL_POS [ m_chsl_id ].DOWN;
		Select ();
	}
	void CharaSele_Cursor::Left ()
	{
		m_chsl_id = CHSL_POS [ m_chsl_id ].LEFT;
		Select ();
	}
	void CharaSele_Cursor::Right ()
	{
		m_chsl_id = CHSL_POS [ m_chsl_id ].RIGHT;
		Select ();
	}

	void CharaSele_Cursor::Select ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_move );
		m_cursor->SetPos ( GetPos ( m_chsl_id ) );
		mwp_player.lock()->SelectChara_cutin ( m_chsl_id );
	}


}	//namespace GAME

