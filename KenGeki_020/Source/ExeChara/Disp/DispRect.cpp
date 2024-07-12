//=================================================================================================
//
// DispRect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispRect.h"
#include "../../FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispRect::DispRect () 
	{
		//枠表示を初期化
#if 0
		m_pvpGrpCRect = make_shared < VP_PrmRect > ();
		m_pvpGrpARect = make_shared < VP_PrmRect > ();
		m_pvpGrpHRect = make_shared < VP_PrmRect > ();
		m_pvpGrpORect = make_shared < VP_PrmRect > ();

		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			m_pvpGrpCRect->push_back ( Make ( RECT_COLOR_C ) );
			m_pvpGrpARect->push_back ( Make ( RECT_COLOR_A ) );
			m_pvpGrpHRect->push_back ( Make ( RECT_COLOR_H ) );
			m_pvpGrpORect->push_back ( Make ( RECT_COLOR_O ) );

		}
#endif // 0

		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			map_GrpCRect.push_back ( Make ( RECT_COLOR_C ) );
			map_GrpHRect.push_back ( Make ( RECT_COLOR_H ) );
			map_GrpARect.push_back ( Make ( RECT_COLOR_A ) );
			map_GrpORect.push_back ( Make ( RECT_COLOR_O ) );
		}

		InitRect ();


//		OnRect ();
	}

	P_PrmRect DispRect::Make ( DWORD clr )
	{
		//----------------------------------------------------
		//@info		GRPLSTに動的に追加するときは既に全体がLoad()されているので、
		//			明示的にLoad()が必要
		//----------------------------------------------------

		P_PrmRect p = std::make_shared < PrmRect > ();
		p->SetColor ( S3d_Utl::DWORD_to_Color ( clr ) );
		p->SetSize ( s3d::Rect::size_type { 0, 0 } );
		p->Load ();
		p->Move ();
		AddpTask ( p );

//		p->SetZ ( Z_SYS );
//		GRPLST_INSERT_MAIN ( p );

		return p;
	}

	DispRect::~DispRect ()
	{
#if 0

		//終了時にグラフィックタスクを外す
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpCRect)[i] );
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpARect)[i] );
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpHRect)[i] );
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpORect)[i] );
		}
		//解放
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			m_pvpGrpCRect->clear ();
			m_pvpGrpARect->clear ();
			m_pvpGrpHRect->clear ();
			m_pvpGrpORect->clear ();
		}

#endif // 0
	}

	//実効枠設定
	void DispRect::SetCharaRect ( P_CharaRect pCharaRect )
	{
		mp_CharaRect = pCharaRect;
	}

	//更新
	void DispRect::Update ()
	{
		SetCRect ( mp_CharaRect->GetpvCRect () );
		SetHRect ( mp_CharaRect->GetpvHRect () );
		SetARect ( mp_CharaRect->GetpvARect () );
		SetORect ( mp_CharaRect->GetpvORect () );
	}

	//表示枠の初期化
	void DispRect::InitRect ()
	{
		for ( P_PrmRect p : map_GrpCRect ) { p->SetZero (); }
		for ( P_PrmRect p : map_GrpHRect ) { p->SetZero (); }
		for ( P_PrmRect p : map_GrpARect ) { p->SetZero (); }
		for ( P_PrmRect p : map_GrpORect ) { p->SetZero (); }
	}

	//表示
	void DispRect::OnRect ()
	{
		for ( P_PrmRect p : map_GrpCRect ) { p->SetValid ( T ); }
		for ( P_PrmRect p : map_GrpHRect ) { p->SetValid ( T ); }
		for ( P_PrmRect p : map_GrpARect ) { p->SetValid ( T ); }
		for ( P_PrmRect p : map_GrpORect ) { p->SetValid ( T ); }
	}

	//非表示
	void DispRect::OffRect ()
	{
		for ( P_PrmRect p : map_GrpCRect ) { p->SetValid ( F ); }
		for ( P_PrmRect p : map_GrpHRect ) { p->SetValid ( F ); }
		for ( P_PrmRect p : map_GrpARect ) { p->SetValid ( F ); }
		for ( P_PrmRect p : map_GrpORect ) { p->SetValid ( F ); }
	}

	//実効枠から表示枠へ設置
	void DispRect::SetGrpRect ( AP_PrmRect& apGrpRect, PV_RECT pvRect )
	{
		float bx = G_BASE_POS().x;	//基準位置

		UINT i = 0;
		for ( P_PrmRect p : apGrpRect )
		{
			RECT r = pvRect->at ( i );
			int32 x = (int32)bx + r.left;
			int32 y = r.top;
			int32 w = r.right - r.left;
			int32 h = r.bottom - r.top;
			p->SetRect ( x, y, w, h );
			++ i;
		}
	}

}	//namespace GAME

