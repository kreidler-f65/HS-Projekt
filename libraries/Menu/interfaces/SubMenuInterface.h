/*
||
|| @file SubMenuIterface.h
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide the interface for making submenuitems
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/

#ifndef SUBMENUINTERFACE_H
#define SUBMENUINTERFACE_H

class SubMenuItem;
class MenuItemInterface;

#define MAXIMUM_SUBMENU_ITEMS 4 

class SubMenuInterface{
    public:
        virtual void up() = 0;
        virtual void down() = 0;
        virtual void previous() = 0;
        virtual bool select(byte select) = 0;
        virtual MenuItemInterface* use();
        
        inline virtual bool addSubMenuItem( SubMenuItem& menuItem ) { return false; };
    private:
        virtual void setCurrentIndex( byte select ) = 0;
};

#endif

/*
|| @changelog
|| | 1.0 2009-04-22 - Alexander Brevig : Initial Release
|| #
*/