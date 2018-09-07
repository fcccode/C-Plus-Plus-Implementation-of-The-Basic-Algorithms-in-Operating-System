// CzhWindows1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

//STEP 1 ����������
WNDCLASSEX wcx;

HINSTANCE hInstance1;//ȫ�־��
HWND  hWndTree;//treeview���
HWND  hWndList;//listview���
HWND hWnd;//�����ھ��
HIMAGELIST m_TreeImageList;//treeviewͼ���
HIMAGELIST m_ListImageList;//listviewͼ���
CString   LVrood,LVrood1;//����·��
map<CString,CString>  Map;//���ش�����Ϣ�ݴ�

//STEP 2 ��ƴ�����
void CzhWindow(HINSTANCE hinstance);



//STEP 3 ���崰�����е�MainWndProc
LRESULT CALLBACK MainWndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK About(HWND,UINT,WPARAM,LPARAM);//˵���Ի���
void TreeInitialization ();//��ʼ��treeview
void ListInitialization();//��ʼ��listview
void ExpandTreeItem(CString str, HTREEITEM rootItem);//��չtreeview�ڵ�
void GetChildItem(LPNMHDR lpnmh);//����treeview�����¼�
void setNewTreeItem(HTREEITEM rootItem,CString str,HWND hwndfrom);//����treeview �����¼��ӽڵ�
void setNewListItemFromTree(CString str);//����treeview�����¼�listview��ʾ
void RefreshList();//���ڸı��listview��ʾ
void setNewListItemFromList(LPNMHDR lpnmh);//listview˫���¼�����
void setMemu(HWND hWnd, WPARAM wParam);//Ϊlistview����Ҽ��˵�


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	hInstance1=hInstance;
	CzhWindow(hInstance1);//STEP 2 ��ƴ�����


	//STEP 4: ע�ᴰ����
	if(!::RegisterClassEx(&wcx))
		return false;
	//STEP 5:��������
	//HWND hWnd;
	hWnd=::CreateWindow("CzhWindows",//����������ע��һ����
						"��Դ������",//����
						WS_OVERLAPPEDWINDOW,//������ʽ
						CW_USEDEFAULT,//ˮƽĬ��λ�á�
						CW_USEDEFAULT,//��ֱĬ��λ��
						CW_USEDEFAULT,//���Ĭ��
						CW_USEDEFAULT,//�߶�Ĭ��
						(HWND)NULL,//�޸�����
						(HMENU)::LoadMenu(hInstance1,MAKEINTRESOURCE(IDR_MENU_MAIN)),//�޲˵�
						//(HMENU)NULL,//�޲˵�
						hInstance,//Ӧ�ó�����
						(LPVOID)NULL//���ڴ���ʱ������
						);
	
	if(!hWnd)
	  return false;
	//STEP 6:��ʾ����
	::ShowWindow(hWnd,nCmdShow);
	::UpdateWindow(hWnd);
	
	//::MessageBox(hWnd,TEXT("ģʽ�Ի���"),TEXT("׽ס����"),MB_OK);
	//STEP 7:��Ϣѭ��

	MSG msg;
	BOOL bGetMessage;//�Ƿ�ɹ���ȡ��Ϣ
	while((bGetMessage=::GetMessage(&msg,(HWND)NULL,0,0))!=0 && bGetMessage !=-1)//����Ϣ������ȡ��Ϣ
	{
		::TranslateMessage(&msg);//ת����Ϣ
		::DispatchMessage(&msg);//�ɷ���Ϣ
	}
		


	return msg.wParam;
}

//STEP 2 ��ƴ����࣬����hinstanceΪ��Ӧ�ó��򱾴����о��

void CzhWindow(HINSTANCE hinstance)
{
	//���wcx�����ݽṹ
	wcx.cbSize=sizeof(wcx);//�ṹ��Ĵ�С
	wcx.style=CS_HREDRAW|CS_VREDRAW;//��ʽ����С�ı�ʱ�ػ����
	wcx.lpfnWndProc=MainWndProc;//������Ϣ������
	wcx.cbClsExtra=0;//�޸��Ӵ������ڴ�
	wcx.cbWndExtra=0;//�޸��Ӵ����ڴ�
	wcx.hInstance=hinstance;//����Ӧ�ó���ʵ�����
	wcx.hIcon=::LoadIcon(NULL,IDI_APPLICATION);//ͼ��Ĭ��
	wcx.hCursor=::LoadCursor(NULL,IDC_ARROW);//���Ĭ��
	wcx.hbrBackground=(HBRUSH)::GetStockObject(WHITE_BRUSH);//������ɫ
	wcx.lpszMenuName=NULL;//��ʹ�ò˵�
	wcx.lpszClassName="CzhWindows";//��������
	wcx.hIconSm=(HICON)::LoadImage(hInstance1,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		::GetSystemMetrics(SM_CXSMICON),
		::GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);//Сͼ��


	return ;
}

//STEP 3 ���崰�����е�MainWndProc

LRESULT CALLBACK MainWndProc(HWND hWnd,//���ھ��
							 UINT uMsg,//��Ϣ��ʾ��
							 WPARAM wParam,//��Ϣ�ĵ�һ������
							 LPARAM lParam)//��Ϣ�ĵڶ�������
{//������Ϣ�ദ������
	//TVINSERTSTRUCT tvInst;
	//HTREEITEM hNode1;
	//HTREEITEM hNode2,hNode3;
	//HTREEITEM hChild1,hChild2;
	HDWP hdwp;
	RECT rect;
	CFileFind finder;
	switch(uMsg)
	{
	case WM_CREATE://����treeview��listview��������ʾ��Դ����������
		GetClientRect(hWnd, &rect);
		hWndTree = CreateWindow(TEXT("SysTreeView32"), TEXT("Simple"),//����treeview
								WS_BORDER | WS_CHILD | WS_VISIBLE |
								TVS_HASLINES |TVS_HASBUTTONS|TVS_LINESATROOT 
								| TVS_SINGLEEXPAND ,
								0, 0, 
								rect.right/4, rect.bottom,
								hWnd, NULL, hInstance1, 0);
		hWndList = CreateWindow("syslistview32", "", //����listview
                                     WS_VISIBLE|WS_CHILD|WS_BORDER|
                                    LVS_ICON | LVS_SHOWSELALWAYS, 
                                    (rect.right/4)+5, 0,
                                    (rect.right/4)*3-3,
                                    rect.bottom, 
                                    hWnd, NULL, hInstance1, NULL);																																		
		TreeInitialization ();//���ó�ʼ������
		ListInitialization ();
		break;
	case WM_DESTROY://�������٣��������ϽǵĹرհ�ť�ᴥ������Ϣ
		::ExitProcess(0);//�������н������߳�
		::ExitThread(0);
		return 0;
		break;
	case WM_COMMAND://����Ӧ�ó���˵�
		switch(LOWORD(wParam))
		{
			//�ڡ��������˵���ѡ�񡰹��ڡ�
		case ID_HELP_ABOUT:
			{
				DialogBox(hInstance1,(LPCSTR)IDD_DIALOG_ABOUT,hWnd,(DLGPROC)About);
				return 0;
			}
		case ID_OPENFILE://�����Ҽ��˵���ѡ�񡰴��ļ���
			{
				
				BOOL beWorking = finder.FindFile(LVrood1+"\\*");
				if(beWorking)//�ж��Ƿ�ΪĿ¼���������listview�������ļ�����ʾ��
				{   
					ListView_DeleteAllItems(hWndList);
					setNewListItemFromTree(LVrood1);
				}
				else//����ֱ�Ӵ��ļ�
					::ShellExecute(hWnd,0,LVrood1,0,0,SW_SHOWNORMAL);
			}

		default:
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
		}
		break;
	case WM_SIZE://�����ڸı�ʱ�ؼ���ʾ����
		hdwp = BeginDeferWindowPos(2);
		GetClientRect(hWnd, &rect);
		DeferWindowPos(hdwp, hWndTree, NULL, 0, 0,//�޸�treeview��С
			rect.right/4, rect.bottom, SWP_NOZORDER);
		DeferWindowPos(hdwp, hWndList, NULL, rect.right/4+5, 0,//�޸�listview��С
			(rect.right/4)*3-3, rect.bottom, SWP_NOZORDER);
		EndDeferWindowPos(hdwp);
		RefreshList();//ˢ��listview��ʾ����
		break;
	case WM_NOTIFY:
	{
		LPNMHDR lpnmh = (LPNMHDR)lParam;
		if(NM_CLICK == lpnmh->code)//�������¼�
		{
			if(lpnmh->hwndFrom==hWndTree)//����treeview�����¼�
				GetChildItem(lpnmh);
		}
		if(NM_DBLCLK == lpnmh->code)//����˫���¼�
		{
			if(lpnmh->hwndFrom==hWndList)//����listview˫���¼�
				
				setNewListItemFromList(lpnmh);
		}
	}
	break;
	case WM_CONTEXTMENU://����listview�Ҽ��˵���ʾ     
    {    
		setMemu(hWnd,wParam);
    }     
    break;
	default://�������Ϣδ��������Ĭ�ϴ�����Ϣ����������
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
		return 0;
}


//����About�Ӵ��ڵ���Ϣ������
LRESULT CALLBACK About(HWND  hDlg,
					   UINT  uMsg,
					   WPARAM  wParam,
					   LPARAM  lParawm)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND://����OK��ť
		if(LOWORD(wParam)==IDOK||LOWORD(wParam)==IDCANCEL)
		{
			::EndDialog(hDlg,LOWORD(wParam));
			return true;
		}
		break;



	}
	return false;

}

void   TreeInitialization ()
{
	TVINSERTSTRUCT tvInst;
	//Root...
	HTREEITEM RootNode;
	SHFILEINFO fileInfo1;
	//��ȡϵͳicon�б������ø�treeview
	m_TreeImageList = (HIMAGELIST) SHGetFileInfo("C:\\",
			0,
			&fileInfo1,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_SMALLICON);//����Сicon
	TreeView_SetImageList(hWndTree,m_TreeImageList,TVSIL_NORMAL); 
	//����treeview�ڵ���Ϣ�������ø��ڵ㡰�ҵĵ��ԡ�
	tvInst.item.mask =  TVIF_IMAGE |TVIF_TEXT | TVIF_SELECTEDIMAGE;
	tvInst.item.iImage=0;
	tvInst.item.iSelectedImage=0;
	tvInst.hInsertAfter = TVI_ROOT;
	tvInst.hParent = NULL;
	tvInst.item.pszText = TEXT("�ҵĵ���");
	RootNode= (HTREEITEM)SendMessage(hWndTree, TVM_INSERTITEM, 0, (LPARAM)&tvInst);
	//��ȡ���ش�����Ϣ
	char buff[1024] = {0};
	GetLogicalDriveStrings(1024, buff);
	char* pTemp = buff;
	while (*(pTemp) != 0)
	{
		CString str,str1="";

		switch(::GetDriveType(pTemp))//�жϴ������ͣ������ʾ��ʾ
		{
		case DRIVE_FIXED:
			str = "���ش���";
			break;
		case DRIVE_REMOVABLE:
			str = "���ƶ�����";
			break;
		case DRIVE_CDROM:
			str = "����";
			break;
		default:
			str = "δ֪����";
			break;
		}
		str = str + "(" + pTemp + ")";
		Map[str]=pTemp;//����map����·����Ϣ��������չ�ڵ�ʱ��·��Ѱ��
		char *s=(LPSTR)(LPCSTR)str;
		//�����½ڵ�
		SHGetFileInfo(pTemp,
			0,
			&fileInfo1,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_SMALLICON);//ѡ��Сicon

		tvInst.hInsertAfter=TVI_LAST;
		tvInst.hParent = RootNode;
		tvInst.item.pszText = s;
		tvInst.item.iImage =fileInfo1.iIcon;
		tvInst.item.iSelectedImage= fileInfo1.iIcon;
		HTREEITEM subItem =(HTREEITEM)SendMessage(hWndTree, TVM_INSERTITEM, 0, (LPARAM)&tvInst);
		//���ô����ӽڵ���Ϣ�����ṩtreeview�ϡ�+����ʾ���д����ļ���
		ExpandTreeItem(pTemp, subItem);
		//�������л�õĴ�����Ϣ
		char* newBuff = new char[6];
		strcpy(newBuff, pTemp);
		pTemp += 4;
		delete newBuff;
	}
		return ;
}

void   ListInitialization ()
{
	LVITEM LVitem;//����listview����Ϣ
	LVitem.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	LVitem.iItem=-1;
	LVitem.lParam=0;
	LVitem.state=0;
	LVitem.stateMask=0;
	LVitem.iSubItem=0;
	LVrood="";//���õ�ǰlistview��ʾ�ļ���·��Ϊ��
	//��ȡϵͳicon�б������ø�treeview
	SHFILEINFO fileInfo2;
	m_ListImageList = (HIMAGELIST) SHGetFileInfo("C:\\",
			0,
			&fileInfo2,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_LARGEICON);//���ô�icon
	ListView_SetImageList(hWndList,m_ListImageList,TVSIL_NORMAL); 
	//ɾ��listview������ʾ
	ListView_DeleteAllItems(hWndList);
	//��ȡ���ش�����Ϣ
	char buff[1024] = {0};
	GetLogicalDriveStrings(1024, buff);
	char* pTemp = buff;
	while (*(pTemp) != 0)
	{
		CString str,str1="";

		switch(::GetDriveType(pTemp))//�жϴ������ͣ������ʾ��ʾ
		{
		case DRIVE_FIXED:
			str = "���ش���";
			break;
		case DRIVE_REMOVABLE:
			str = "���ƶ�����";
			break;
		case DRIVE_CDROM:
			str = "����";
			break;
		default:
			str = "δ֪����";
			break;
		}
		str = str + "(" + pTemp + ")";
		char *s=(LPSTR)(LPCSTR)str;
		//������ʾ��
		SHGetFileInfo(pTemp,
			0,
			&fileInfo2,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_LARGEICON);//���ô�icon
		LVitem.iImage=fileInfo2.iIcon;
		LVitem.pszText=s;
		LVitem.iItem++;
		//��������ʾ��
		ListView_InsertItem(hWndList,&LVitem);
		//�������л�õĴ�����Ϣ
		char* newBuff = new char[6];
		strcpy(newBuff, pTemp);
		pTemp += 4;
		delete newBuff;
	}
		return ;
}

void ExpandTreeItem(CString str, HTREEITEM rootItem)
{
	TVINSERTSTRUCT tvInst;
	tvInst.item.mask =  TVIF_IMAGE |TVIF_TEXT | TVIF_SELECTEDIMAGE;//���ýڵ���ʾ��������
    CString tempStr = str;
	str += "\\*";
	CFileFind finder;
	//��ȡ����·�����ļ���Ϣ
	BOOL beWorking = finder.FindFile(str);
	SHFILEINFO fileInfo;
	
	while (beWorking)//ѭ��������õ��ļ���Ϣ��ֻ��ʾ�ļ�����Ϣ
	{
		beWorking = finder.FindNextFile();//˳���ȡ�ļ�
		if (finder.IsDots())//ȥ��. ..Ŀ¼
		{
			continue;
		}
		CString fileName = finder.GetFileName();
		if(!finder.IsDirectory())//ֻ����Ŀ¼���������½ڵ�
		{
			continue;
 		}	
		HTREEITEM subItem ;
		CString tempStr1 = finder.GetFilePath();
		char* newBuf = new char[1024];
		//���ýڵ���Ϣ
		strcpy(newBuf, tempStr1.GetBuffer(0));
				SHGetFileInfo(tempStr1,
			0,
			&fileInfo,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_SMALLICON);//����Сicon
		tvInst.hInsertAfter=TVI_LAST;
		tvInst.hParent = rootItem;
		tvInst.item.iImage=fileInfo.iIcon;
		tvInst.item.iSelectedImage=fileInfo.iIcon;
		tvInst.item.pszText =(LPSTR)(LPCSTR)fileName;
		//����½ڵ�
		subItem =(HTREEITEM)SendMessage(hWndTree, TVM_INSERTITEM, 0, (LPARAM)&tvInst);
		
	}
}

void GetChildItem(LPNMHDR lpnmh)
{
	CString  name,rootroad="";
	//��ȡ����¼�����
	DWORD dwPos = GetMessagePos();
	POINT pt;
	pt.x = LOWORD(dwPos);
	pt.y = HIWORD(dwPos);
	//ת��Ϊ�ͻ�������
	ScreenToClient(lpnmh->hwndFrom, &pt);
	//��ȡ����¼�����treeview��iItem���
	TVHITTESTINFO ht = {0};
	ht.pt = pt;
	ht.flags = TVHT_ONITEM;
	HTREEITEM hItem1 = TreeView_HitTest(lpnmh->hwndFrom, &ht);
	HTREEITEM hItem2,hItem=hItem1;	
	//���ýڵ���Ϣ
	TVITEM ti = {0};
	ti.mask = TVIF_HANDLE | TVIF_TEXT;//���û�ȡ�ڵ�����
	TCHAR buf[1024] = {0};
	ti.cchTextMax = 1024;
	ti.pszText = buf;
	ti.hItem = hItem1;
	//tvInst.item=ti;
	TreeView_GetItem(lpnmh->hwndFrom, &ti);//��ʼ��name����ȡ�ڵ�����
	name=ti.pszText;
	//��ȡ���ڵ㣬�жϵ���¼��Ľڵ��Ƿ�Ϊ���ڵ㣬�����������treeview
	hItem2=TreeView_GetParent(lpnmh->hwndFrom,hItem1);//��ȡ���ڵ�
	if( hItem2!=0)
	{
		if(Map.find(name)==Map.end())//�ж��Ƿ�Ϊ���̽ڵ�
		{
			rootroad=name;//ѭ��ȡ�ýڵ���ļ�·��
			while(1)
			{
				ti.hItem = hItem2;
				TreeView_GetItem(lpnmh->hwndFrom, &ti);//��ȡ�ڵ�text
				name=ti.pszText;
				if(Map.find(name)!=Map.end())//���̽ڵ����˳�ѭ��
					break;
				//���·��
				rootroad="\\"+rootroad;
				rootroad=ti.pszText+rootroad;
				hItem1=hItem2;
				hItem2=TreeView_GetParent(lpnmh->hwndFrom,hItem1);//ѭ��ȡ�ø��ڵ�
			}
		}
		rootroad=Map[name]+rootroad;//�������·��
		setNewTreeItem(hItem,rootroad,lpnmh->hwndFrom);//������������treeview�½ڵ㺯��
		setNewListItemFromTree(rootroad);//��������listview��ʾ���
	}
	else//Ϊ���ڵ�������ˢ��listviewΪ��ʼ״̬
		ListInitialization ();
}

void setNewTreeItem(HTREEITEM rootItem,CString str,HWND  hwndfrom)
{
	HTREEITEM hItem1,hItem2;
	CString  str1;
	//�����½ڵ���Ϣ
	TVITEM ti = {0};
	str;
	ti.mask = TVIF_HANDLE | TVIF_TEXT;
	TCHAR buf[1024] = {0};
	ti.cchTextMax = 1024;
	ti.pszText = buf;
	//��ȡ����ڵ���ӽڵ㣬������ڵ���Ϣ��������treeview�д���ڵ�ġ�+������Ϣ����ʾ��ʾ����
	hItem1=TreeView_GetChild(hwndfrom,rootItem);
	while(hItem1!=NULL)//�жϵ�һ�ν���ʱ�Ƿ�Ϊ�����ļ��нڵ㣬������������������ӽڵ㡰+������Ϣ
					   //���ѭ���ж��Ƿ񵽴���·�������һ�����ļ��нڵ�
	{
		//�жϴ���ڵ��Ƿ��Ѿ������ӽڵ㣬�����������
		hItem2=TreeView_GetChild(hwndfrom,hItem1);
		if(hItem2!=NULL)
			return ;
		ti.hItem = hItem1;
		//�������·��������ExpandTreeItem���ڸ��½ڵ���Ϣ
		TreeView_GetItem(hwndfrom, &ti);
		str1=str+"\\"+ti.pszText;
		LVrood=str1;//����listview·����Ϣ
		ExpandTreeItem(str1, hItem1);
		hItem1=TreeView_GetNextVisible(hwndfrom,hItem1);//��ȡ��һ���ӽڵ�
	}
	return ;
}

void setNewListItemFromTree(CString str)
{
	ListView_DeleteAllItems(hWndList);//ɾ��listviewԭ����ʾ��
	// �����µ���ʾ��
	LVITEM LVitem;       
	LVitem.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	LVitem.iItem=-1;
	LVitem.lParam=0;
	LVitem.state=0;
	LVitem.stateMask=0;
	LVitem.iSubItem=0;
	LVrood=str;
	//����·��
    CString tempStr = str;
	str += "\\*";
	//��ȡ����·�����ļ���Ϣ
	CFileFind finder;
	BOOL beWorking = finder.FindFile(str);
	SHFILEINFO fileInfo2;
	
	while (beWorking)//ѭ��������õ��ļ���Ϣ����ʾȫ���ļ�
	{
		beWorking = finder.FindNextFile();//˳���ȡ�ļ�
		CString fileName = finder.GetFileName();
		if (finder.IsDots())//ȥ��. ..Ŀ¼
		{
			continue;
		}
		CString tempStr1 = finder.GetFilePath();
		//������ʾ��
		char *s=(LPSTR)(LPCSTR)fileName;
		char* newBuf = new char[1024];
		strcpy(newBuf, tempStr1.GetBuffer(0));
				SHGetFileInfo(tempStr1,
			0,
			&fileInfo2,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_LARGEICON);//����Ϊ��icon
		LVitem.iImage=fileInfo2.iIcon;
		LVitem.pszText=s;
		LVitem.iItem++;
		ListView_InsertItem(hWndList,&LVitem);//������ʾ��
	}
	return ;
}

void setNewListItemFromList(LPNMHDR lpnmh)
{
	CString root;
	CFileFind finder;
	TCHAR buf[1024] = {0};
	//���ñ��������Ϣ
	LVITEM LVitem;// ��
	LVitem.mask=LVIF_TEXT;
	LVitem.cchTextMax=1024;
	LVitem.pszText=buf;
	NM_LISTVIEW* pNMTreeView = (NM_LISTVIEW*)lpnmh;
	LVitem.iItem=pNMTreeView->iItem;
	//��ȡ��������ı�
	ListView_GetItemText(lpnmh->hwndFrom,LVitem.iItem,0,buf,LVitem.cchTextMax);
	//�����·��
	if(Map.find(LVitem.pszText)==Map.end())
		root=LVrood+"\\"+LVitem.pszText;
	else
		root=LVrood+Map[LVitem.pszText];
	//�ж��Ƿ�Ϊ�ļ���
	BOOL beWorking = finder.FindFile(root+"\\*");
	if(beWorking)//����ɾ��listview��IItem������ʾ�ļ���������
	{   
		ListView_DeleteAllItems(hWndList);
		setNewListItemFromTree(root);
	}
	else//����ֱ�����г���
		::ShellExecute(hWnd,0,root,0,0,SW_SHOWNORMAL);
	return ;
}

void RefreshList()
{
	if(LVrood=="")//�ж�listview���ļ�·���Ƿ�Ϊ���ڵ�
		ListInitialization ();//�������³�ʼ������
	else
		setNewListItemFromTree(LVrood);//������ݵ�ǰ·����ˢ��listview��ʾ����
	return ;
}

void setMemu(HWND hWnd, WPARAM wParam)
{
	
	HMENU hpop;
	DWORD dwPos = GetMessagePos();
	POINT pt1,pt2;
	pt1.x = LOWORD(dwPos);
	pt1.y = HIWORD(dwPos);
	RECT rect; 
	//��ȡ�ͻ������С     
	GetClientRect(hWndList, &rect); 
	//����Ļ����תΪ�ͻ�������     
	ScreenToClient(hWndList, &pt1);     
    //�жϵ��Ƿ�λ�ڿͻ�������     
    if(!PtInRect(&rect, pt1))    
		return ;
    //���ز˵���Դ
    HMENU hroot1 = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDR_MENU1));
	HMENU hroot2 = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDR_MENU2));
    if(hroot1 && hroot2)     
    {     
           
       // ��ȡ����һ��ǵ�����          
		pt2.x = LOWORD(dwPos);
		pt2.y = HIWORD(dwPos);
        //��ʾ��ݲ˵�     
		LVHITTESTINFO lvpi;
		lvpi.pt=pt1;
		lvpi.flags=LVHT_ABOVE;
		int item=ListView_HitTest(hWndList,&lvpi);
		// ��ȡ��һ�������˵�
		if(item==-1)
			hpop = GetSubMenu(hroot2,0);   
		else 
		{
			hpop = GetSubMenu(hroot1,0);
			//�����Ҽ��˵������ļ�ʱ��·������
			TCHAR buf[1024] = {0};
			LVITEM LVitem;// ���õ�ǰ������
			LVitem.mask=LVIF_TEXT;
			LVitem.cchTextMax=1024;
			LVitem.pszText=buf;
			LVitem.iItem=item;
			ListView_GetItemText(hWndList,LVitem.iItem,0,buf,LVitem.cchTextMax);//��ȡ��ǰ���ı�
			//�����·��
			if(Map.find(LVitem.pszText)==Map.end())
				LVrood1=LVrood+"\\"+LVitem.pszText;
			else
				LVrood1=LVrood+Map[LVitem.pszText];
	
			
		}
		//������ʾλ��
        TrackPopupMenu(hpop,     
        TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,     
		pt2.x,     
        pt2.y,     
        0,
        (HWND)wParam,     
        NULL);     
        // �����Ҫ���ٲ˵���Դ     
        DestroyMenu(hroot1); 
		DestroyMenu(hroot2);
     }     
	return ;
}