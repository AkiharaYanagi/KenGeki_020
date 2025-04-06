//=================================================================================================
//
//	_CharaSele_State
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_CharaSele_State.h"
#include "_CharaSele.h"
#include "_CharaSele_Actor.h"
#include "_CharaSele_Player.h"
#include "../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//----------------------------------------
	void ChSl_St_Chara::Move ()
	{
	}

	void ChSl_St_Chara::Input ()
	{
		//カーソルの移動
		m_cursor->Input ();

		//ボタン0でキャラの決定
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN0 ) )
		{
			Decide ();
		}
	}

	//決定
	void ChSl_St_Chara::Decide ()
	{
		m_cursor->Stop ();

		//ステートを移行
		mwp_Actor.lock()->Start_Clr ();
		mwp_Player.lock()->To_Color ();

		SND_PLAY_ONESHOT_SE ( SE_select_decide );
	}

	//----------------------------------------
	void ChSl_St_Color::Move ()
	{
	}

	void ChSl_St_Color::Input ()
	{
		//左右で色指定
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_LEFT ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
			CHARA_COLOR clr = mwp_Player.lock()->GetColor ();
			CHARA_COLOR prev_clr = CH_CLR_2;
			if ( clr == CH_CLR_2 ) { prev_clr = CH_CLR_1; }
			mwp_Player.lock()->SelectColor_cutin ( prev_clr );
		}
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_RIGHT ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
			CHARA_COLOR clr = mwp_Player.lock()->GetColor ();
			CHARA_COLOR next_clr = CH_CLR_2;
			if ( clr == CH_CLR_2 ) { next_clr = CH_CLR_1; }
			mwp_Player.lock()->SelectColor_cutin ( next_clr );
		}

		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN0 ) )
		{
			Decide ();
		}

		//ボタン１でキャンセルして戻る
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN1 ) )
		{
			Cancel ();
		}
	}

	//決定
	void ChSl_St_Color::Decide ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_decide );

		//ステートを移行
		mwp_CharaSele.lock()->Stage_On ();
		mwp_Actor.lock()->Start_Stg ();
		mwp_Player.lock()->To_Stage ();
	}

	//キャンセル
	void ChSl_St_Color::Cancel ()
	{
#if 0
		m_decided = F;
		m_chara_stand->SetValid ( T );
		m_chara_stand_light->SetValid ( F );
		m_cursor->Start ();

		//ステートを変更
		m_state = STT_CHARA;
		m_state_Disp->SetPosY ( CH_STT_CHARA_Y );

		m_wait = 0;
#endif // 0
		//ステートを移行
		mwp_Actor.lock()->Start_Ch ();
		mwp_Player.lock()->To_Chara ();

		SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
	}

	//----------------------------------------
	void ChSl_St_Stage::Move ()
	{
	}

	void ChSl_St_Stage::Input ()
	{
		//左右で選択
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_LEFT ) )
		{
			mwp_CharaSele.lock()->Stage_Prev ();
		}
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_RIGHT ) )
		{
			mwp_CharaSele.lock()->Stage_Next ();
		}

		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN0 ) )
		{
			Decide ();
		}

		//ボタン１でキャンセルして戻る
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN1 ) )
		{
			Cancel ();
		}
	}

	//決定
	void ChSl_St_Stage::Decide ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_decide );

		//ステートを移行
		mwp_CharaSele.lock()->Stage_Off ();
		mwp_CharaSele.lock()->BGM_On ();
		mwp_Actor.lock()->Start_BGM ();
		mwp_Player.lock()->To_BGM ();
	}

	//キャンセル
	void ChSl_St_Stage::Cancel ()
	{
		//ステートを移行
		mwp_CharaSele.lock()->Stage_Off ();
		mwp_Actor.lock()->Start_Clr ();
		mwp_Player.lock()->To_Color ();

		SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
	}

	//----------------------------------------
	void ChSl_St_BGM::Move ()
	{
	}

	void ChSl_St_BGM::Input ()
	{
		//左右で選択
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_LEFT ) )
		{
			mwp_CharaSele.lock()->BGM_Prev ();
		}
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_RIGHT ) )
		{
			mwp_CharaSele.lock()->BGM_Next ();
		}

		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN0 ) )
		{
			Decide ();
		}

		//ボタン１でキャンセルして戻る
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN1 ) )
		{
			Cancel ();
		}
	}

	//決定
	void ChSl_St_BGM::Decide ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_decide );

		//ステートを移行
		PLAYER_ID id = mwp_Player.lock()->GetPlayerID ();
		if ( PLAYER_ID_1 == id )
		{
			mwp_CharaSele.lock()->OK_On_1p ();
		}
		else if ( PLAYER_ID_2 == id )
		{
			mwp_CharaSele.lock()->OK_On_2p ();
		}
		mwp_Player.lock()->To_OK ();
		mwp_Actor.lock()->Start_OK ();
	}

	//キャンセル
	void ChSl_St_BGM::Cancel ()
	{
		//ステートを移行
		mwp_CharaSele.lock()->Stage_On ();
		mwp_Player.lock()->To_Stage ();
		mwp_Actor.lock()->Start_Stg ();

		SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
	}

	//----------------------------------------
	void ChSl_St_OK::Move ()
	{
	}

	void ChSl_St_OK::Input ()
	{
		//ボタン１でキャンセルして戻る
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN1 ) )
		{
			Cancel ();
		}
	}

	//キャンセル
	void ChSl_St_OK::Cancel ()
	{
		//ステートを移行
		PLAYER_ID id = mwp_Player.lock()->GetPlayerID ();
		if ( PLAYER_ID_1 == id )
		{
			mwp_CharaSele.lock()->OK_Off_1p ();
		}
		else if ( PLAYER_ID_2 == id )
		{
			mwp_CharaSele.lock()->OK_Off_2p ();
		}
		mwp_CharaSele.lock()->BGM_On ();
		mwp_Player.lock()->To_BGM ();
		mwp_Actor.lock()->Start_BGM ();

		SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
	}




}	//namespace GAME

