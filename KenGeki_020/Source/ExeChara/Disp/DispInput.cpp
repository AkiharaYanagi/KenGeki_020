//=================================================================================================
//
// DispInput ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キー入力表示個数
	//@todo CharaInputの入力保存数と同一なので統合する
	const uint32 DispInput::NUM_DISP_INPUT = 20;
	const int32 DispInput::BASE_X = 10;
	const int32 DispInput::BASE_Y = 150;
	const int32 DispInput::CHIP_W = 10;
	const int32 DispInput::CHIP_H = 10;


	//コンストラクタ
	DispInput::DispInput ()
//		: m_timer ( 0 ), m_vel ( 1.f ), m_base_x ( 10 )
	{
		//---------------------------------------------------------------
		//背景
		m_bg = std::make_shared < PrmRect > ();
		m_bg->SetColor ( ColorF ( 0.5f, 0.75f, 0.5f, 0.5f ) );

#if 0
		//---------------------------------------------------------------
		//背景
		m_bg->SetRect ( m_base_x, BASE_Y, CHIP_W * INPUT_NUM, CHIP_H * NUM_DISP_INPUT );
		m_bg->SetZ ( Z_SYS + 0.01f );
		m_bg->SetAllColor ( 0x8080a080 );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		//---------------------------------------------------------------
		//見出
		m_index = make_shared < GrpAcv > ();
		m_index->AddTexture ( _T ( "KeyIndex.png" ) );
		m_index->SetPos ( VEC2 ( m_base_x, BASE_Y - CHIP_H ) );
		m_index->SetZ ( Z_SYS );
		AddpTask ( m_index );
		GRPLST_INSERT_MAIN ( m_index );

		//---------------------------------------------------------------
		//キー入力
		m_grp = make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "10_10_white.png" ) );
		m_grp->SetZ ( Z_SYS - 0.01f );
		m_grp->ClearObject ();
#endif // 0

		//-----------------------------------------------------
		//矩形管理 ( 12種類 * 60[FPS] )
		//縦 60FPS
		for ( UINT frame = 0; frame < NUM_DISP_INPUT; ++ frame )
		{
			//横 8種類
			for ( UINT i = 0; i < PLY_INPUT_NUM; ++ i )
			{
				P_Ob pOb = std::make_shared < GameObject > ();
				pOb->SetPos ( m_x + 10.f * i, 10.f + 10 * frame );
				map_Ob.push_back ( pOb );

				//初期値ランダム
				pOb->SetValid ( 0 == rand () % 2  );
			}
		}

//		AddpTask ( m_grp );
//		GRPLST_INSERT_MAIN ( m_grp );
		
		//-----------------------------------------------------

	}

	DispInput::~DispInput ()
	{
	}


	//プレイヤIDによる表示初期化
	void DispInput::LoadPlayer ( PLAYER_ID playerID )
	{
		//位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_x = 10;
		}
		else
		{
			m_x = 1280 - 10 - CHIP_W * PLY_INPUT_NUM;
		}

		m_bg->SetRect ( m_x, BASE_Y, CHIP_W * PLY_INPUT_NUM, CHIP_H * NUM_DISP_INPUT );

		int i = 0;
		for ( P_Ob pOb: map_Ob )
		{
			int frame = i / PLY_INPUT_NUM;
			int input = i % PLY_INPUT_NUM;
			pOb->SetPos ( m_x + 10.f * input, BASE_Y + 10.f * frame );
			++ i;
		}

#if 0
		m_index->SetPos ( VEC2 ( m_base_x, BASE_Y - CHIP_H ) );
#endif // 0

		m_timer = 0;
	}


	//更新
	void DispInput::UpdateInput ( P_CharaInput pCharaInput )
	{

		//---------------------------------------------------------------
		//キー過去入力の表示
		++ m_timer;

		//1マス分移動したら上にシフト
		if ( 0 < m_timer )
		{
			//上書のため逆順ループ
			for ( size_t i = map_Ob.size () - 1; i >= PLY_INPUT_NUM; -- i )
			{
				map_Ob [ i ]->SetValid ( map_Ob [ i - PLY_INPUT_NUM ]->GetValid () );
			}

			m_timer = 0;
		}

		//--------------------------
		//現入力の反映
		V_GAME_KEY vKey = pCharaInput->GetvGameKey ();

		//表示位置
		int i = 0;
		for ( P_Ob pOb: map_Ob )
		{
			int frame = i / PLY_INPUT_NUM;
			int input = i % PLY_INPUT_NUM;
			pOb->SetValid ( GetBoolInput ( pCharaInput, frame, input ) );
			pOb->SetPos ( m_x + 10.f * input, BASE_Y + 10 * frame + m_vel * m_timer );
			++ i;
		}

		//---------------------------------------------------------------
	}


	//描画
	void DispInput::Draw ()
	{
		//背景
		m_bg->Draw ();

		//キー入力
		for ( P_Ob pOb: map_Ob )
		{
			if ( ! pOb->GetValid () ) { continue; }

			int32 x = (int32)pOb->GetPos().x;
			int32 y = (int32)pOb->GetPos().y;
			int32 w = CHIP_W;
			int32 h = CHIP_H;
			s3d::Rect rect { x, y, w, h };
			rect.draw ();
		}

		TASK_VEC::Draw ();
	}

	//-------------------------------------
	//内部利用
	//n:キー種類, i:[F]
	bool DispInput::GetBoolInput ( P_CharaInput pCharaInput, int n, int i )
	{
		//現入力
		const V_GAME_KEY& vKey = pCharaInput->GetvGameKey ();

		bool ret = false;
		switch ( i )
		{
		case  0: ret = vKey [ n ].GetLvr ( GameKey::LVR_4 ); break;
		case  1: ret = vKey [ n ].GetLvr ( GameKey::LVR_2 ); break;
		case  2: ret = vKey [ n ].GetLvr ( GameKey::LVR_6 ); break;
		case  3: ret = vKey [ n ].GetLvr ( GameKey::LVR_8 ); break;
		case  4: ret = vKey [ n ].GetBtn ( GameKey::BTN_0 ); break;
		case  5: ret = vKey [ n ].GetBtn ( GameKey::BTN_1 ); break;
		case  6: ret = vKey [ n ].GetBtn ( GameKey::BTN_2 ); break;
		case  7: ret = vKey [ n ].GetBtn ( GameKey::BTN_3 ); break;
		case  8: ret = vKey [ n ].GetBtn ( GameKey::BTN_4 ); break;
		case  9: ret = vKey [ n ].GetBtn ( GameKey::BTN_5 ); break;
		case 10: ret = vKey [ n ].GetBtn ( GameKey::BTN_6 ); break;
		case 11: ret = vKey [ n ].GetBtn ( GameKey::BTN_7 ); break;
		default: break;
		}
		return ret;
	}


	void DispInput::On ()
	{
#if 0
		m_bg->SetValid ( T );
		m_index->SetValid ( T );
		m_grp->SetValid ( T );
#endif // 0
	}

	void DispInput::Off ()
	{
#if 0
		m_bg->SetValid ( F );
		m_index->SetValid ( F );
		m_grp->SetValid ( F );
#endif // 0
	}


}	//namespace GAME

