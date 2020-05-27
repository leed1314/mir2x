/*
 * =====================================================================================
 *
 *       Filename: layoutboard.hpp
 *        Created: 03/25/2020 22:27:45
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#pragma once
#include <list>
#include <array>
#include <vector>
#include <memory>
#include <functional>
#include "widget.hpp"
#include "xmltypeset.hpp"

class LayoutBoard: public Widget
{
    private:
        struct parNode
        {
            // margin[0]  up
            // margin[1]  down
            // margin[2]  left
            // margin[3]  right

            int startY = -1;
            std::array<int, 4> margin {0, 0, 0, 0};
            std::unique_ptr<XMLTypeset> tpset; // no copy support for XMLTypeset
        };

    private:
        std::list<parNode> m_parNodeList;

    private:
        struct parNodeConfig
        {
            // default setup of paragraph in LayoutBoard
            // may needed this to support theme

            int lineWidth;
            std::array<int, 4> margin;

            bool canThrough;

            uint8_t  font;
            uint8_t  fontSize;
            uint8_t  fontStyle;
            uint32_t fontColor;
            uint32_t fontBGColor;

            int align;
            int lineSpace;
            int wordSpace;

        } m_parNodeConfig;

    private:
        bool m_canSelect;

    private:
        const std::function<void(const std::string &, int, int)> m_eventCB;

    public:
        LayoutBoard(
                int x,
                int y,
                int lineWidth,

                bool            canSelect = false,
                std::array<int, 4> margin = {0, 0, 0, 0},

                bool canThrough = false,

                uint8_t  font        =  0,
                uint8_t  fontSize    = 10,
                uint8_t  fontStyle   =  0,
                uint32_t fontColor   =  colorf::WHITE + 255,
                uint32_t fontBGColor =  colorf::WHITE,

                int lineAlign = LALIGN_LEFT,
                int lineSpace = 0,
                int wordSpace = 0,

                const std::function<void(const std::string &, int, int)> &eventCB = nullptr,

                Widget *parent     =  nullptr,
                bool    autoDelete =  false)
            : Widget(x, y, 0, 0, parent, autoDelete)
            , m_parNodeConfig
              {
                  lineWidth,
                  margin,
                  canThrough,
                  font,
                  fontSize,
                  fontStyle,
                  fontColor,
                  fontBGColor,
                  lineAlign,
                  lineSpace,
                  wordSpace,
              }
            , m_canSelect(canSelect)
            , m_eventCB(eventCB)
        {
            if(m_parNodeConfig.lineWidth <= m_parNodeConfig.margin[2] + m_parNodeConfig.margin[3]){
                throw fflerror("invalid default paragraph parameters");
            }
        }

    public:
        void loadXML(const char *);

    public:
        void addParXML(int, const std::array<int, 4> &, const char *);

    public:
        void update(double ms) override
        {
            for(const auto &node: m_parNodeList){
                node.tpset->update(ms);
            }
        }

    public:
        int parCount() const
        {
            return (int)(m_parNodeList.size());
        }

    private:
        auto ithParIterator(int i)
        {
            auto p = m_parNodeList.begin();
            std::advance(p, i);
            return p;
        }

    public:
        bool empty() const
        {
            return m_parNodeList.empty();
        }

        void clear()
        {
            m_parNodeList.clear();
        }

    public:
        void setFont(uint8_t font)
        {
            m_parNodeConfig.font = font;
        }

        void setFontSize(uint8_t fontSize)
        {
            m_parNodeConfig.fontSize = fontSize;
        }

        void setFontStyle(uint8_t fontStyle)
        {
            m_parNodeConfig.fontStyle = fontStyle;
        }

        void setFontColor(uint32_t fontColor)
        {
            m_parNodeConfig.fontColor = fontColor;
        }

        void setFontBGColor(uint32_t fontBGColor)
        {
            m_parNodeConfig.fontBGColor = fontBGColor;
        }

        void setLineWidth(int)
        {
        }

    public:
        void drawEx(int, int, int, int, int, int) override;
        bool processEvent(const SDL_Event &, bool) override;

    private:
        void setupSize();
        void addPar(int, const std::array<int, 4> &, const tinyxml2::XMLNode *, bool);
};
