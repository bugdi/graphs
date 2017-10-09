#include "window.h"
#include "file.h"
#include "loop.h"

#include <strsafe.h> /* yeah */

#define ID_NEW 0
#define ID_OPEN 1
#define ID_SAVE 2
#define ID_EXIT 3

void create_menu(HWND hwnd)
{
	HMENU hMenubar = CreateMenu();
	HMENU hFile = CreateMenu();

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, "File");

	AppendMenu(hFile, MF_STRING, ID_NEW, "New");
	AppendMenu(hFile, MF_STRING, ID_OPEN, "Open");
	AppendMenu(hFile, MF_STRING, ID_SAVE, "Save");
	AppendMenu(hFile, MF_STRING, ID_EXIT, "Exit");

	SetMenu(hwnd, hMenubar);
}

void SetWindowTitle(LPSTR lpstrFile, size_t nFileOffset)
{
	LPSTR newWindowTitle;
	size_t fileNameLength;
	StringCchLength(&lpstrFile[nFileOffset], MAX_PATH, &fileNameLength);
	newWindowTitle = (LPSTR)malloc(sizeof(CHAR) * (fileNameLength + 10));

	StringCchCopy(newWindowTitle, (fileNameLength + 10), &lpstrFile[nFileOffset]);
	StringCchCat(newWindowTitle, (fileNameLength + 10), " - Graph");

	SDL_SetWindowTitle(gWindow, newWindowTitle);

	free(newWindowTitle);
}

void WindowsOpenGraph(HWND hwnd)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_PATH];       // buffer for file name
	//HWND hwnd;              // owner window
	HANDLE hf;              // file handle

							// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Graph (*.gph)\0*.gph";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn) == TRUE)
	{
		gGraph = load_graph(ofn.lpstrFile);
		SetWindowTitle(ofn.lpstrFile, ofn.nFileOffset);
	}
}

void WindowsSaveGraph(HWND hwnd)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_PATH];       // buffer for file name
	//HWND hwnd;              // owner window
	HANDLE hf;              // file handle
	LPSTR newWindowTitle;
	size_t strFileLength;

							// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Graph (*.gph)\0*.gph";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrDefExt = "gph";
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	// Display the Open dialog box. 

	if (GetSaveFileName(&ofn) == TRUE)
	{
		save_graph(gGraph, ofn.lpstrFile);
		SetWindowTitle(ofn.lpstrFile, ofn.nFileOffset);
	}
}



void window_command(HWND hWnd, WORD lwParam)
{
	OPENFILENAME openFileName;
	switch (lwParam)
	{
	case ID_OPEN:
		WindowsOpenGraph(hWnd);
		break;
	case ID_SAVE:
		WindowsSaveGraph(hWnd);
		break;
	case ID_EXIT:
		exit(0);
		break;
	}
}