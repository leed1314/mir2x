#pragma once
#include <vector>
#include <FL/Fl_Box.H>
#include <cstdint>
#include <FL/Fl_Shared_Image.H>
#include <functional>

class DrawArea: public Fl_Box
{
    private:
        int m_MouseX;
        int m_MouseY;

        int m_OffsetX; // location of (0, 0) on DrawArea
        int m_OffsetY;

    private:
        Fl_Image *m_TUC[4]; // triangle unit cover
        Fl_Image *m_TextBoxBG;     // backgound for living text

    public:
        DrawArea(int, int, int, int);
        ~DrawArea();

    public:
        // required overriding function
        void draw();
        int  handle(int);

    public:
        void SetOffset(int, bool, int, bool);

    private:
        void    DrawBaseTile();
        void    DrawGroundObject();
        void    DrawOverGroundObject();
        void    DrawFunction(Fl_Image *, int, int);
        void    DrawFunction(uint32_t, uint32_t, int, int);
        void    DrawGroundInfo();

    private:
        void    DrawSelect();
        void    DrawTrySelect();
        void    DrawTextBox();

    private:
        void RhombusCoverOperation(int, int, int, std::function<void(int, int, int)>);
        void RectangleCoverOperation(int, int, int, std::function<void(int, int, int)>);

    private:
        void DrawSelectBySingle();
        void DrawSelectByRegion();
        void DrawSelectByRhombus();
        void DrawSelectByRectangle();

    private:
        void AddSelect();

    private:
        void AddSelectBySingle();
        void AddSelectByRegion();
        void AddSelectByRhombus();
        void AddSelectByRectangle();

    private:
        void GetTriangleOnMap(int, int, int, int &, int &, int &, int &, int &, int &);
        bool LocateGroundSubCell(int, int, int &, int &, int &);
        void SetGroundSubCellUnderPoint(int, int);

    public:
        Fl_Image *CreateTUC(int);
        void ClearSelectTUC();
        void SetSelectTUC(int, int, int, int);
        void SetScrollBar();

    public:
        void DrawTUC(int, int, int);
};