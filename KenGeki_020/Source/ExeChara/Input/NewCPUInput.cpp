//=================================================================================================
//
// NewCPUInput ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "NewCPUInput.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
	//重み定数
	const std::vector < double > NewCPUInput::weights =
	{
		0.1,		//LVR_1		下後(dir変換)
		0.3,		//LVR_2		下
		0.2,		//LVR_3		下前(dir変換)
		0.4,		//LVR_4		後(dir変換)
	};
#endif // 0


	//重み定数：レバー
#if 0
	const std::vector < double > NewCPUInput::weights =
	{
		10,		//LVR_1		下後(dir変換)
		15,		//LVR_2		下
		10,		//LVR_3		下前(dir変換)
		0,		//LVR_4		後(dir変換)
		1000,	//LVR_5		N
		600,	//LVR_6		前(dir変換)
		10,		//LVR_7		上後(dir変換)
		10,		//LVR_8		上
		20,		//LVR_9		上前(dir変換)
	};
#endif // 0
	//右方向共通
	const std::vector < double > NewCPUInput::weights =
	{
		10,		//LVR_1		下後
		15,		//LVR_2		下
		10,		//LVR_3		下前
		0,		//LVR_4		後
		800,	//LVR_5		N
		90,		//LVR_6		前
		10,		//LVR_7		上後
		10,		//LVR_8		上
		30,		//LVR_9		上前
	};

	//重み定数：ボタン
	const std::vector < double > NewCPUInput::weights_key =
	{
		2000,	//N							0
		120,	//BTN_0		(小)				1
		100,	//BTN_1		(中)				2
		 80,	//BTN_2		(大)				3
		 50,	//BTN_3		(特大)			4
		 10,	//BTN_4		(必殺)			5
		 50,	//BTN_5		(ダッシュ)		6

		20,		//BTN_3 + LVR_6 (剣撃走破)	7
		10,		//BTN_4 + LVR_6 (波動必殺)	8
		10,		//BTN_4 + LVR_4 (竜巻必殺)	9
		10,		//BTN_4 + LVR_2 (昇竜拳)		10
		10,		//BTN_4 + BTN_2 (超必殺A)	11
		10,		//BTN_4 + BTN_3 (超必殺B)	12
	};




	NewCPUInput::NewCPUInput ()
	{

#if 0
		std::vector < double > weights = { 0.1, 0.3, 0.2, 0.4 };
		m_dist = std::discrete_distribution <> ( weights.begin(), weights.end() );
#endif // 0

		//初期値を現在時刻で１ｐと２ｐで変える
		std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now ();
		std::chrono::duration ms = std::chrono::duration_cast < std::chrono::milliseconds > ( now.time_since_epoch () );
		int32_t t = static_cast < int32_t > ( ms.count() );

		m_gen = std::mt19937 ( (unsigned int)t + m_rnd_dev () );	//メルセンヌ・ツイスタ
	}


	NewCPUInput::~NewCPUInput ()
	{
	}


	void NewCPUInput::Load ()
	{
	}

	void NewCPUInput::Update ( bool dirRight )
	{
		(void)dirRight;

		GameKey gameKey;

#if 0

				//test
		std::mt19937 m_gen;
		std::discrete_distribution<> m_dist;
		std::random_device m_rnd_dev;

		m_gen = std::mt19937 ( m_rnd_dev () );		//メルセンヌ・ツイスタ
#endif // 0
		m_dist = std::discrete_distribution <> ( weights.begin(), weights.end() );

		int result = 0;


#if 0

		int num [ 8 ] = { 0 };


		for ( int i = 0; i < 10000; ++ i )
		{
			result = m_dist ( m_gen );

			switch ( result )
			{
			case 0: ++ num [ 0 ]; break;
			case 1: ++ num [ 1 ]; break;
			case 2: ++ num [ 2 ]; break;
			case 3: ++ num [ 3 ]; break;
			case 4: ++ num [ 4 ]; break;
			case 5: ++ num [ 5 ]; break;
			case 6: ++ num [ 6 ]; break;
			case 7: ++ num [ 7 ]; break;
			}
		}

		for ( int i = 0; i < 8; ++ i )
		{
			TRACE_F ( _T("%d, "), num [ i ]  );
		}

#endif // 0


#if 0

		int result = 0;

		for ( int i = 0; i < 100; ++ i )
		{
			result = m_dist ( m_gen );
			TRACE_F ( _T("%d, "), result );
		}
		TRACE_F ( _T("\n"), result );

#endif // 0


		result = m_dist ( m_gen );
		//result = s3d::Random < int > ( 0, 8 );

		//今回の入力をゲームキーに直して保存
		//  (ゲームキー保存は右方向共通で、コマンド入力側で向きを反映している)
		switch ( result )
		{
		case 0: gameKey.SetLvr ( GameKey::LVR_1, T ); break;
		case 1:	gameKey.SetLvr ( GameKey::LVR_2, T ); break;
		case 2:	gameKey.SetLvr ( GameKey::LVR_3, T ); break;
		case 3: gameKey.SetLvr ( GameKey::LVR_4, T ); break;
		case 4:	/* Neutral */						  break;
		case 5: gameKey.SetLvr ( GameKey::LVR_6, T ); break;
		case 6: gameKey.SetLvr ( GameKey::LVR_7, T ); break;
		case 7: gameKey.SetLvr ( GameKey::LVR_8, T ); break;
		case 8: gameKey.SetLvr ( GameKey::LVR_9, T ); break;

		default: break;
		}

		//左右チェック
#if 0
		if ( ! dirRight )
		{
			//1<->3, 4<->6, 7<->9
			switch ( result )
			{
			case 0: gameKey.SetLvr ( GameKey::LVR_3, T ); break;
			case 1:	gameKey.SetLvr ( GameKey::LVR_2, T ); break;
			case 2:	gameKey.SetLvr ( GameKey::LVR_1, T ); break;
			case 3: gameKey.SetLvr ( GameKey::LVR_6, T ); break;
			case 4:	/* Neutral */						  break;
			case 5: gameKey.SetLvr ( GameKey::LVR_4, T ); break;
			case 6: gameKey.SetLvr ( GameKey::LVR_9, T ); break;
			case 7: gameKey.SetLvr ( GameKey::LVR_8, T ); break;
			case 8: gameKey.SetLvr ( GameKey::LVR_7, T ); break;
			default: break;
			}
		}
		else
		{
			switch ( result )
			{
			case 0: gameKey.SetLvr ( GameKey::LVR_1, T ); break;
			case 1:	gameKey.SetLvr ( GameKey::LVR_2, T ); break;
			case 2:	gameKey.SetLvr ( GameKey::LVR_3, T ); break;
			case 3: gameKey.SetLvr ( GameKey::LVR_4, T ); break;
			case 4:	/* Neutral */						  break;
			case 5: gameKey.SetLvr ( GameKey::LVR_6, T ); break;
			case 6: gameKey.SetLvr ( GameKey::LVR_7, T ); break;
			case 7: gameKey.SetLvr ( GameKey::LVR_8, T ); break;
			case 8: gameKey.SetLvr ( GameKey::LVR_9, T ); break;

			default: break;
			}
		}
#endif // 0



		//============================================================
		//ボタン
#if 0
		1000,		//N						0
		60,		//BTN_0		(小)				1
		50,		//BTN_1		(中)				2
		40,		//BTN_2		(大)				3
		30,		//BTN_3		(特大)			4
		10,		//BTN_4		(必殺)			5
		20,		//BTN_5		(ダッシュ)		6

		50,		//BTN_3 + LVR_6 (剣撃走破)	7
		20,		//BTN_4 + LVR_6 (波動必殺)	8
		20,		//BTN_4 + LVR_4 (竜巻必殺)	9
		20,		//BTN_4 + LVR_2 (昇竜拳)		10
		20,		//BTN_4 + BTN_2 (超必殺A)	11
		20,		//BTN_4 + BTN_3 (超必殺B)	12
#endif // 0


		m_dist_key = std::discrete_distribution <> ( weights_key.begin(), weights_key.end() );

		int result_key = 0;
		result_key = m_dist_key ( m_gen );

		switch ( result_key )
		{
		case 0: 	/* Neutral */					  break;
		case 1: gameKey.SetBtn ( GameKey::BTN_0, T ); break;
		case 2:	gameKey.SetBtn ( GameKey::BTN_1, T ); break;
		case 3:	gameKey.SetBtn ( GameKey::BTN_2, T ); break;
		case 4: gameKey.SetBtn ( GameKey::BTN_3, T ); break;
		case 5: gameKey.SetBtn ( GameKey::BTN_4, T ); break;
		case 6: gameKey.SetBtn ( GameKey::BTN_5, T ); break;

		case 7:
			gameKey.SetBtn ( GameKey::BTN_3, T );
			gameKey.SetLvr ( GameKey::LVR_6, T );
		break;

		case 8:
			gameKey.SetBtn ( GameKey::BTN_4, T );
			gameKey.SetLvr ( GameKey::LVR_6, T );
		break;

		case 9:
			gameKey.SetBtn ( GameKey::BTN_4, T );
			gameKey.SetLvr ( GameKey::LVR_4, T );
		break;

		case 10:
			gameKey.SetBtn ( GameKey::BTN_4, T );
			gameKey.SetLvr ( GameKey::LVR_2, T );
		break;

		case 11:
			gameKey.SetBtn ( GameKey::BTN_4, T );
			gameKey.SetBtn ( GameKey::BTN_2, T );
		break;

		case 12:
			gameKey.SetBtn ( GameKey::BTN_4, T );
			gameKey.SetBtn ( GameKey::BTN_3, T );
		break;

		default: break;
		}


		IncrementInput ( gameKey );
	}



}	//namespace GAME

