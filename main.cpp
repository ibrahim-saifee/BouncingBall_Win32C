#define _WIN32_WINNT 0x0500
#include <windows.h>
#include<stdio.h>
#include<Mmsystem.h>

#define SIZE 15
#define SIZE2 10
#define SIZE3 20
#define g 1
#define BALL_TIMER 1
#define ID_OBSTACLE 1
#define WINLOSE_TIMER 2

struct object
{int x,y,xdir,ydir,vvel,hvel;};

int winlose;
HINSTANCE hinstance;
HBITMAP hBitmapDesert;//hBitmapFire;

void printstatus( HDC hdc)
{
HFONT hfont;
LOGFONT f={0};
strcpy(f.lfFaceName,"Arial Black");
 f.lfHeight=70;
 f.lfPitchAndFamily=FIXED_PITCH;
 hfont=CreateFontIndirect(&f);
 SetTextColor(hdc,RGB(100,50,255));
 SetBkMode(hdc,TRANSPARENT);
 SelectObject(hdc,hfont);
 switch(winlose)
 {case 1:
 TextOut(hdc,600,300,"You did it",10);
 break;
 case 2:
 TextOut(hdc,600,300,"You Down",8);
 break;
 case 3:
 TextOut(hdc,500,300,"Evil Hit You",12);
 break;
 case 4:
 TextOut(hdc,600,200,"Welcome!",8);
 TextOut(hdc,605,270,"By Saifee",9);
 break;
 }
 DeleteObject(hfont);
}


void physics(HWND hwnd,HWND hwndRect[],object *ob)
{int vs,hs,i;
RECT rc;
POINT pt1,pt2;

rc.left=ob->x-SIZE3-1;  rc.right=ob->x+SIZE3+1;
rc.top=ob->y-SIZE3-1;    rc.bottom=ob->y+SIZE3+1;
InvalidateRect(hwnd,&rc,FALSE);
	
	vs=ob->vvel;
	hs=ob->hvel;
	ob->vvel=ob->vvel+(ob->ydir*g);
	/*	if(ob->ydir<0)
			{ob->vvel-=g;ob->y=ob->y-vs;}
			if(ob->ydir>0)
			{ob->vvel+=g;ob->y=ob->y+vs;}
		*/	
	ob->y=ob->y+(ob->ydir*vs);
	ob->x=ob->x+(ob->xdir*hs);
	
	for(i=0;i<7;i++)
	{GetWindowRect(hwndRect[i],&rc);
	pt1.x=rc.left;pt1.y=rc.top;pt2.x=rc.right;pt2.y=rc.bottom;
	ScreenToClient(hwnd,&pt1); ScreenToClient(hwnd,&pt2);
	if(ob->x>=pt1.x && ob->x<=pt2.x)
	if(ob->y>pt1.y-SIZE && ob->y<pt2.y+SIZE)
	{
	if(ob->ydir>0){ob->ydir=-1;ob->hvel=-1;ob->vvel-=3;ob->y=pt1.y-SIZE;}
	else if(ob->ydir<0){ob->ydir=1;ob->hvel-=1;ob->y=pt2.y+SIZE;}
    //sndPlaySound(WAV, SND_ASYNC);
    //hResInfo=FindResource(hinstance,MAKEINTRESOURCE(200),"WAVE");
    //hRes=LoadResource(hinstance,(HRSRC)hResInfo);
    //lpRes=(char*)LockResource(hRes);
//    sndPlaySound(lpRes, SND_MEMORY | SND_SYNC | SND_NODEFAULT);
      PlaySound(MAKEINTRESOURCE(200),hinstance,SND_RESOURCE|SND_ASYNC|SND_NOSTOP);
    //UnlockResource(hRes);
	}
	}
	
	GetClientRect(hwnd,&rc);
	
	if(ob->x>=10 && ob->x<=60 && ob->y>=0 && ob->y<=90)
	{ob->x=rc.right-SIZE-90;ob->y=rc.bottom-SIZE-150;
	 ob->ydir=1;ob->hvel=ob->vvel=0;
	 //MessageBox(hwnd,"Goal!","Game",MB_OK);
	 PlaySound(MAKEINTRESOURCE(201),hinstance,SND_RESOURCE|SND_ASYNC);
	 winlose=1;
	 SetTimer(hwnd,WINLOSE_TIMER,1000,NULL);
	 InvalidateRect(hwnd,NULL,FALSE);
	}
	
	if(ob->x<SIZE){ob->xdir=1;ob->hvel-=1;ob->x=SIZE;PlaySound(MAKEINTRESOURCE(200),hinstance,SND_RESOURCE|SND_ASYNC|SND_NOSTOP);}
	if(ob->x>rc.right-SIZE){ob->xdir=-1;ob->hvel-=1;ob->x=rc.right-SIZE;PlaySound(MAKEINTRESOURCE(200),hinstance,SND_RESOURCE|SND_ASYNC|SND_NOSTOP);}
	
	if(ob->y<=SIZE){ob->ydir=1;ob->hvel-=1;ob->y=SIZE;PlaySound(MAKEINTRESOURCE(200),hinstance,SND_RESOURCE|SND_ASYNC|SND_NOSTOP);}
	//if(ob->y>=rc.bottom-SIZE){ob->ydir=-1;ob->vvel-=3;ob->hvel-=1;ob->y=rc.bottom-SIZE;}
	if(ob->y>=rc.bottom-SIZE){ob->ydir=1;ob->x=rc.right-SIZE-90;ob->y=rc.bottom-SIZE-150;
						  ob->hvel=ob->vvel=0;
						  winlose=2;SetTimer(hwnd,WINLOSE_TIMER,1000,NULL);InvalidateRect(hwnd,NULL,FALSE);}
	
	if(ob->vvel<0){ob->ydir=1;ob->vvel=0;}if(ob->hvel<0)ob->hvel=0;	

rc.left=ob->x-SIZE3-1;  rc.right=ob->x+SIZE3+1;
rc.top=ob->y-SIZE3-1;    rc.bottom=ob->y+SIZE3+1;
InvalidateRect(hwnd,&rc,FALSE);
}


void evilphysics(HWND hwnd,HWND hwndRect[],object *ob)
{int vs,hs,i;
RECT rc;
POINT pt1,pt2;

rc.left=ob->x-SIZE3-1;  rc.right=ob->x+SIZE3+1;
rc.top=ob->y-SIZE3-1;    rc.bottom=ob->y+SIZE3+1;
InvalidateRect(hwnd,&rc,FALSE);

	if(ob->xdir>0)ob->x+=ob->hvel;
	else ob->x-=ob->hvel;
	
	if(ob->ydir>0)ob->y+=ob->vvel;
	else ob->y-=ob->vvel;
	
	for(i=0;i<7;i++)
	{GetWindowRect(hwndRect[i],&rc);
	pt1.x=rc.left;pt1.y=rc.top;pt2.x=rc.right;pt2.y=rc.bottom;
	ScreenToClient(hwnd,&pt1); ScreenToClient(hwnd,&pt2);
	if(ob->x>=pt1.x && ob->x<=pt2.x)
	if(ob->y>pt1.y-SIZE3 && ob->y<pt2.y+SIZE3)
	{
	if(ob->ydir>0){ob->ydir=-1;ob->y=pt1.y-SIZE3;}
	else if(ob->ydir<0){ob->ydir=1;ob->y=pt2.y+SIZE3;}
	}
	}
	
	GetClientRect(hwnd,&rc);
		
	if(ob->x<SIZE3){ob->xdir=1;ob->x=SIZE3;}
	if(ob->x>rc.right-SIZE3){ob->xdir=-1;ob->x=rc.right-SIZE3;}
	
	if(ob->y<=SIZE3){ob->ydir=1;ob->y=SIZE3;}
	if(ob->y>=rc.bottom-SIZE3){ob->ydir=-1;ob->y=rc.bottom-SIZE3;}

rc.left=ob->x-SIZE3-1;  rc.right=ob->x+SIZE3+1;
rc.top=ob->y-SIZE3-1;    rc.bottom=ob->y+SIZE3+1;
InvalidateRect(hwnd,&rc,FALSE);
}


void collision(HWND hwnd,object *ob,object *obe1, object *obe2)
{int x1=0,y1,x2,y2;
RECT rc;
GetClientRect(hwnd,&rc);
  x1=ob->x-SIZE3; y1=ob->y-SIZE3;
  x2=ob->x+SIZE3; y2=ob->y+SIZE3;
     if((x1>obe1->x-SIZE3 && x1<obe1->x+SIZE3) && ((y1>obe1->y-SIZE3 && y1<obe1->y+SIZE3)||(y2>obe1->y-SIZE3 && y2<obe1->y+SIZE3)))
        x1=3;
     if((x2>obe1->x-SIZE3 && x2<obe1->x+SIZE3) && ((y1>obe1->y-SIZE3 && y1<obe1->y+SIZE3)||(y2>obe1->y-SIZE3 && y2<obe1->y+SIZE3)))
        x1=3;
        
     if((x1>obe2->x-SIZE3 && x1<obe2->x+SIZE3) && ((y1>obe2->y-SIZE3 && y1<obe2->y+SIZE3)||(y2>obe2->y-SIZE3 && y2<obe2->y+SIZE3)))
        x1=3;
     if((x2>obe2->x-SIZE3 && x2<obe2->x+SIZE3) && ((y1>obe2->y-SIZE3 && y1<obe2->y+SIZE3)||(y2>obe2->y-SIZE3 && y2<obe2->y+SIZE3)))
        x1=3;

if(x1==3){winlose=3;ob->ydir=1;ob->x=rc.right-SIZE-90;ob->y=rc.bottom-SIZE-150;ob->hvel=ob->vvel=0;SetTimer(hwnd,WINLOSE_TIMER,1000,NULL);InvalidateRect(hwnd,NULL,FALSE);}
}


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
HDC hdc,hdcMem,hdcBuffer;
HBITMAP hBitmapBuffer;
PAINTSTRUCT ps;
HPEN hPen;
HBRUSH hBrush;
RECT rc;
int i,j;
POINT pt1,pt2;
static BOOL pick;
static object ball,evilball[2];
static HWND hwndRect[7];

	switch(Message) {
		
		case WM_CREATE:
			
			GetClientRect(hwnd,&rc);
			
			ball.x=rc.right-SIZE-90;ball.y=rc.bottom-SIZE-150;
			 ball.ydir=1;ball.hvel=ball.vvel=0;
			 evilball[0].vvel=evilball[0].hvel=5;
			 evilball[0].x=evilball[0].y=SIZE3;
			 evilball[1].vvel=evilball[1].hvel=5;
			 evilball[1].x=rc.right-SIZE3; evilball[1].y=SIZE3;
			 
			for(i=0;i<7;i++)
			hwndRect[i] = CreateWindow (TEXT ("static"), NULL,	WS_CHILD | WS_VISIBLE | SS_BLACKRECT|SS_BLACKFRAME,200*i, 100*(i+1), 100, 10,hwnd, (HMENU) i, hinstance, NULL);
			
			PlaySound(MAKEINTRESOURCE(201),hinstance,SND_RESOURCE|SND_ASYNC);
            winlose=4;
            SetTimer(hwnd,WINLOSE_TIMER,1000,NULL);
			//hBitmapFire=LoadBitmap(hinstance,MAKEINTRESOURCE(900));
			hBitmapDesert=LoadBitmap(hinstance,MAKEINTRESOURCE(500));
			//hBitmap=(HBITMAP)LoadImage(NULL,"fire.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			SetTimer(hwnd,BALL_TIMER,10,NULL);
            break;
		
		case WM_TIMER:
		switch(wParam)
		{
		case BALL_TIMER:
			physics(hwnd,hwndRect,&ball);
			evilphysics(hwnd,hwndRect,&evilball[0]);
			evilphysics(hwnd,hwndRect,&evilball[1]);
			collision(hwnd,&ball,&evilball[0],&evilball[1]);
			//InvalidateRect(hwnd,NULL,TRUE);
			break;
			
		case WINLOSE_TIMER:
			winlose=0;
			KillTimer(hwnd,WINLOSE_TIMER);
			InvalidateRect(hwnd,NULL,TRUE);
			break;	
		}
		break;
	
			
		case WM_KEYDOWN:
			GetClientRect(hwnd,&rc);
			switch(wParam)
			{
            case VK_SPACE:
            case VK_UP:
				ball.vvel=20;
				ball.ydir=-1;
				break;
			case VK_RIGHT:
				ball.hvel=5;
				ball.xdir=1;
				break;
			case VK_LEFT:
				ball.hvel=5;
				ball.xdir=-1;
				break;
			case VK_DOWN:
                 if(ball.ydir<0)
                 ball.vvel=0;
                 break;
			}
			break;
			
		case WM_ERASEBKGND:
            break;
		case WM_PAINT:
			GetClientRect(hwnd,&rc);
            hdc=BeginPaint(hwnd,&ps);
			hdcBuffer=CreateCompatibleDC(hdc);
			hBitmapBuffer=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
            SelectObject(hdcBuffer,hBitmapBuffer);
            hdcMem=CreateCompatibleDC(hdc);
			SelectObject(hdcMem,hBitmapDesert);
            StretchBlt(hdcBuffer,0,0,rc.right,rc.bottom,hdcMem,0,0,768,512,MERGECOPY);
			DeleteDC(hdcMem);
			
            hPen=CreatePen(PS_SOLID,3,RGB(0,0,0));
			hBrush=CreateSolidBrush(RGB(0,255,255));
			Rectangle(hdcBuffer,10,0,60,90);
			TextOut(hdcBuffer,20,10,"GOAL",4);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			
			hPen=CreatePen(PS_SOLID,2,RGB(155,0,0));
			hBrush=CreateSolidBrush(RGB(155,0,0));
			GetClientRect(hwnd,&rc);
			SelectObject(hdcBuffer,hPen);
			SelectObject(hdcBuffer,hBrush);
			Ellipse(hdcBuffer,ball.x-SIZE,ball.y-SIZE,ball.x+SIZE,ball.y+SIZE);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			
			hPen=CreatePen(PS_SOLID,2,RGB(0,155,0));
			hBrush=CreateSolidBrush(RGB(0,155,0));
			GetClientRect(hwnd,&rc);
			SelectObject(hdcBuffer,hPen);
			SelectObject(hdcBuffer,hBrush);
			for(i=0;i<2;i++)
            Ellipse(hdcBuffer,evilball[i].x-SIZE3,evilball[i].y-SIZE3,evilball[i].x+SIZE3,evilball[i].y+SIZE3);
            DeleteObject(hBrush);
			DeleteObject(hPen);
			
			if(winlose>0)printstatus(hdcBuffer);
			BitBlt(hdc,0,0,rc.right,rc.bottom,hdcBuffer,0,0,SRCCOPY);
			DeleteDC(hdcBuffer);
			DeleteObject(hBitmapBuffer);
			EndPaint(hwnd,&ps);		
			break;
			
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: 
			KillTimer(hwnd,1);
			PostQuitMessage(0);
			break;
	
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
hinstance=hInstance;
	HWND hwnd;
	WNDCLASSEX wc; /* A properties struct of our window */
	MSG Msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//CreateSolidBrush(RGB(255,255,255));
	//wc.hbrBackground=(HBRUSH)LoadBitmap(hinstance,MAKEINTRESOURCE(500));
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon (hInstance, MAKEINTRESOURCE(100)); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon (hInstance, MAKEINTRESOURCE(100)); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
RECT rc;
GetWindowRect(GetDesktopWindow(),&rc);
	hwnd = CreateWindowEx(0,//WS_EX_LAYERED|WS_EX_TOPMOST,
                               "WindowClass","Bouncing Ball",
								WS_CLIPCHILDREN|WS_POPUP,
								rc.left,rc.top,
								rc.right,rc.bottom,
								NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	ShowWindow(hwnd,SW_SHOW);
	//SetLayeredWindowAttributes(hwnd,RGB(255,1,1),255,2);

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&Msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&Msg); /* Translate key codes to chars if present */
		DispatchMessage(&Msg); /* Send it to WndProc */
	}
	return Msg.wParam;
	
}
