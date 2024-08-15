//=================================================================================================
//
//	BattleTime ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "BattleTime.h"
#include "../FtgConst.h"	
#include "../../GameMain/G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const int BattleTime::START_TIME = 3600;	//60秒
//	const int BattleTime::START_TIME = 1800;	//30秒
//	const int BattleTime::START_TIME = 359;		//テスト用５秒

	BattleTime::BattleTime ()
	{
		//------------------------------------------------
		//背景
		m_time_bg = std::make_shared < GameGraphic > ();
		m_time_bg->AddTexture_FromArchive ( U"time\\time_bg0.png" );
		m_time_bg->SetPos ( VEC2 ( (1280 / 2) - (256 / 2), 12 ) );
		m_time_bg->SetZ ( Z_BG - 0.01f );
		AddpTask ( m_time_bg );
		GRPLST_INSERT ( m_time_bg );

		//数値
		m_battle_time = std::make_shared < GameGraphic > ();
		m_battle_time->AddTexture_FromArchive ( U"time\\time_0.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_1.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_2.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_3.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_4.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_5.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_6.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_7.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_8.png" );
		m_battle_time->AddTexture_FromArchive ( U"time\\time_9.png" );

		AddpTask ( m_battle_time );
		GRPLST_INSERT ( m_battle_time );

		m_battle_time_01 = std::make_shared < GameObject > ();
		m_battle_time_02 = std::make_shared < GameObject > ();
		m_battle_time->ClearObject ();
		m_battle_time->AddpObject ( m_battle_time_01 );
		m_battle_time->AddpObject ( m_battle_time_02 );

		float bx = 16 + (1280 * 0.5f) - (128 / 2);
		float by = 50;
		m_battle_time_01->SetPos ( VEC2 ( bx + 34,	by ) );
		m_battle_time_02->SetPos ( VEC2 ( bx,		by ) );

		//開始状態
		Start ();
	}

	BattleTime::~BattleTime ()
	{
	}

	void BattleTime::Init ()
	{
		m_time = START_TIME;

		TASK_VEC::Init ();
	}

	void BattleTime::Move ()
	{
		//非稼働時は何もしない
		if ( ! m_active ) { TASK_VEC::Move (); return; }

		//--------------------------
		// バトルタイム
		int second = m_time / 60;			//[F] to [Sec]
		int index_01 = second % 10;			//１桁目
		int index_02 = second / 10 % 10;	//2桁目

		m_battle_time_01->SetIndexTexture ( index_01 );
		m_battle_time_02->SetIndexTexture ( index_02 );


		//範囲
//		if ( m_time <= 0 ) { m_time = 3660; }
		if ( m_time <= 0 )
		{
			m_time = 0; 
		}
		else
		{
			-- m_time;
		}

		TASK_VEC::Move ();
	}

	bool BattleTime::IsTimeUp ()
	{
		if ( m_time <= 60 ) { return T; }
		return F;
	}

	void BattleTime::Set ()
	{
		m_time = START_TIME; 

		//--------------------------
		// バトルタイム
		int second = m_time / 60;			//[F] to [Sec]
		int index_01 = second % 10;			//１桁目
		int index_02 = second / 10 % 10;	//2桁目

		m_battle_time_01->SetIndexTexture ( index_01 );
		m_battle_time_02->SetIndexTexture ( index_02 );

	}

	void BattleTime::On ()
	{
		m_time_bg->SetValid ( T );
		m_battle_time_01->SetValid ( T );
		m_battle_time_02->SetValid ( T );
		m_battle_time->SetValid ( T );
	}

	void BattleTime::Off ()
	{
		m_time_bg->SetValid ( F );
		m_battle_time_01->SetValid ( F );
		m_battle_time_02->SetValid ( F );
		m_battle_time->SetValid ( F );
	}


}	//namespace GAME

