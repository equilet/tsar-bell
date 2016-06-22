//----------------------------------------------------------
// name: "tsarWeeded"
//
// Code generated with Faust 0.9.73 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with : "" */
#include <CCinstrument.h>
#include <math.h>
#include <tsarCFweeded.h>
#include <tsarXweeded.h>
#include <tsarYweeded.h>
#include <tsarZweeded.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline float faustpower(float x)          { return powf(x,N); } 
template <int N> inline double faustpower(double x)        { return pow(x,N); }
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
#endif
/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2004-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either version 3
	of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.

	MAX MSP SDK : in order to compile a MaxMSP external with this
	architecture file you will need the official MaxMSP SDK from
	cycling'74. Please check the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

#ifdef WIN32
#ifndef NAN
    static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif
#endif

#define FAUSTFLOAT double

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

class JSONUI : public PathBuilder, public Meta, public UI
{

    protected:
    
        std::stringstream fJSON;
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fName;
        std::string fExpandedCode;
        std::string fSHAKey;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
        
        void init(const std::string& name, int inputs, int outputs, const std::string& sha_key, const std::string& dsp_code)
        {
            fTab = 1;
            
            // Start Meta generation
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fInputs = inputs;
            fOutputs = outputs;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
        }
        
        inline std::string flatten(const std::string& src)
        {
            std::stringstream dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        dst << ' ';
                        break;
                    case '"':
                        dst << "\\" << '"';
                        break;
                    default:
                        dst << src[i];
                        break;
                }
            }
            return dst.str();
        }
      
     public:
     
        JSONUI(const std::string& name, int inputs, int outputs, const std::string& sha_key, const std::string& dsp_code)
        {
            init(name, inputs, outputs, sha_key, dsp_code);
        }

        JSONUI(const std::string& name, int inputs, int outputs)
        {
            init(name, inputs, outputs, "", "");
        }

        JSONUI(int inputs, int outputs)
        {
            init("", inputs, outputs, "", "");
        }
        
        JSONUI()
        {
            init("", -1, -1, "", "");
        }
 
        virtual ~JSONUI() {}

        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            fControlsLevel.push_back(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab + 1);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            fControlsLevel.pop_back();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
    
        virtual void addGenericButton(const char* label, const char* name)
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            addMeta(fTab + 1, false);
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ",";
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"init\": \"" << init << "\",";
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\",";
            tab(fTab + 1, fUI); fUI << "\"step\": \"" << step << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ",";
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            fJSON << "{";
            fTab += 1;
            tab(fTab, fJSON); fJSON << "\"name\": \"" << fName << "\",";
            if (fSHAKey != "") { tab(fTab, fJSON); fJSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, fJSON); fJSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, fJSON); fJSON << "\"inputs\": \"" << fInputs << "\","; 
            tab(fTab, fJSON); fJSON << "\"outputs\": \"" << fOutputs << "\",";
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                fJSON << fMeta.str() << fUI.str();
            } else {
                fJSON << fUI.str();
            }
            tab(fTab, fJSON); fJSON << "}" << std::endl;
            return (flat) ? flatten(fJSON.str()) : fJSON.str();
        }
    
};

#endif // FAUST_JSONUI_H
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;

//----------------------------------------------------------------
//  Signal processor definition
//----------------------------------------------------------------

class dsp {

    protected:

        int fSamplingFreq;

    public:

        dsp() {}
        virtual ~dsp() {}

        virtual int getNumInputs() 										= 0;
        virtual int getNumOutputs() 									= 0;
        virtual void buildUserInterface(UI* ui_interface) 				= 0;
        virtual void init(int samplingRate) 							= 0;
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 	= 0;
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs()                          { return fDSP->getNumInputs(); }
        virtual int getNumOutputs()                         { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface)   { fDSP->buildUserInterface(ui_interface); }
        virtual void init(int samplingRate)                 { fDSP->init(samplingRate); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

//----------------------------------------------------------------
// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
//----------------------------------------------------------------

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>


using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }
inline int int2pow2(int x)		{ int r=0; while ((1<<r)<x) r++; return r; }

long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec3[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec3[i] = 0;
		}
		void fill (int count, double output[]) {
			for (int i=0; i<count; i++) {
				iRec3[0] = (1 + iRec3[1]);
				output[i] = readMarmstk1(int(((iRec3[0] - 1) % 251)));
				// post processing
				iRec3[1] = iRec3[0];
			}
		}
	};


	double 	fConst0;
	int 	iConst1;
	double 	fConst2;
	FAUSTFLOAT 	fslider0;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fentry0;
	double 	fConst4;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fbutton0;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider5;
	static double 	ftbl0[251];
	double 	fRec4[2];
	double 	fRec1[2];
	double 	fRec0[3];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fRec5[3];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fRec6[3];
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fRec7[3];
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fRec8[3];
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fRec9[3];
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fRec10[3];
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fRec11[3];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fRec12[3];
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec13[3];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec14[3];
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec15[3];
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec16[3];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fRec17[3];
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fRec18[3];
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fRec19[3];
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fRec20[3];
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fRec21[3];
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fRec22[3];
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fRec23[3];
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fRec24[3];
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fRec25[3];
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fRec26[3];
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fRec27[3];
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fRec28[3];
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
	double 	fConst104;
	double 	fRec29[3];
	double 	fConst105;
	double 	fConst106;
	double 	fConst107;
	double 	fConst108;
	double 	fRec30[3];
	double 	fConst109;
	double 	fConst110;
	double 	fConst111;
	double 	fConst112;
	double 	fRec31[3];
	double 	fConst113;
	double 	fConst114;
	double 	fConst115;
	double 	fConst116;
	double 	fRec32[3];
	double 	fConst117;
	double 	fConst118;
	double 	fConst119;
	double 	fConst120;
	double 	fRec33[3];
	double 	fConst121;
	double 	fConst122;
	double 	fConst123;
	double 	fConst124;
	double 	fRec34[3];
	double 	fConst125;
	double 	fConst126;
	double 	fConst127;
	double 	fConst128;
	double 	fRec35[3];
	double 	fConst129;
	double 	fConst130;
	double 	fConst131;
	double 	fConst132;
	double 	fRec36[3];
	double 	fConst133;
	double 	fConst134;
	double 	fConst135;
	double 	fConst136;
	double 	fRec37[3];
	double 	fConst137;
	double 	fConst138;
	double 	fConst139;
	double 	fConst140;
	double 	fRec38[3];
	double 	fConst141;
	double 	fConst142;
	double 	fConst143;
	double 	fConst144;
	double 	fRec39[3];
	double 	fConst145;
	double 	fConst146;
	double 	fConst147;
	double 	fConst148;
	double 	fRec40[3];
	double 	fConst149;
	double 	fConst150;
	double 	fConst151;
	double 	fConst152;
	double 	fRec41[3];
	double 	fConst153;
	double 	fConst154;
	double 	fConst155;
	double 	fConst156;
	double 	fRec42[3];
	double 	fConst157;
	double 	fConst158;
	double 	fConst159;
	double 	fConst160;
	double 	fRec43[3];
	double 	fConst161;
	double 	fConst162;
	double 	fConst163;
	double 	fConst164;
	double 	fRec44[3];
	double 	fConst165;
	double 	fConst166;
	double 	fConst167;
	double 	fConst168;
	double 	fRec45[3];
	double 	fConst169;
	double 	fConst170;
	double 	fConst171;
	double 	fConst172;
	double 	fRec46[3];
	double 	fConst173;
	double 	fConst174;
	double 	fConst175;
	double 	fConst176;
	double 	fRec47[3];
	double 	fConst177;
	double 	fConst178;
	double 	fConst179;
	double 	fConst180;
	double 	fRec48[3];
	double 	fConst181;
	double 	fConst182;
	double 	fConst183;
	double 	fConst184;
	double 	fRec49[3];
	double 	fConst185;
	double 	fConst186;
	double 	fConst187;
	double 	fConst188;
	double 	fRec50[3];
	double 	fConst189;
	double 	fConst190;
	double 	fConst191;
	double 	fConst192;
	double 	fRec51[3];
	double 	fConst193;
	double 	fConst194;
	double 	fConst195;
	double 	fConst196;
	double 	fRec52[3];
	double 	fConst197;
	double 	fConst198;
	double 	fConst199;
	double 	fConst200;
	double 	fRec53[3];
	double 	fConst201;
	double 	fConst202;
	double 	fConst203;
	double 	fConst204;
	double 	fRec54[3];
	double 	fConst205;
	double 	fConst206;
	double 	fConst207;
	double 	fConst208;
	double 	fRec55[3];
	double 	fConst209;
	double 	fConst210;
	double 	fConst211;
	double 	fConst212;
	double 	fRec56[3];
	double 	fConst213;
	double 	fConst214;
	double 	fConst215;
	double 	fConst216;
	double 	fRec57[3];
	double 	fConst217;
	double 	fConst218;
	double 	fConst219;
	double 	fConst220;
	double 	fRec58[3];
	double 	fConst221;
	double 	fConst222;
	double 	fConst223;
	double 	fConst224;
	double 	fRec59[3];
	double 	fConst225;
	double 	fConst226;
	double 	fConst227;
	double 	fConst228;
	double 	fRec60[3];
	double 	fConst229;
	double 	fConst230;
	double 	fConst231;
	double 	fConst232;
	double 	fRec61[3];
	double 	fConst233;
	double 	fConst234;
	double 	fConst235;
	double 	fConst236;
	double 	fRec62[3];
	double 	fConst237;
	double 	fConst238;
	double 	fConst239;
	double 	fConst240;
	double 	fRec63[3];
	double 	fConst241;
	double 	fConst242;
	double 	fConst243;
	double 	fConst244;
	double 	fRec64[3];
	double 	fConst245;
	double 	fRec65[3];
	double 	fConst246;
	double 	fRec66[3];
	double 	fConst247;
	double 	fRec67[3];
	double 	fConst248;
	double 	fRec68[3];
	double 	fConst249;
	double 	fRec69[3];
	double 	fConst250;
	double 	fRec70[3];
	double 	fConst251;
	double 	fRec71[3];
	double 	fConst252;
	double 	fRec72[3];
	double 	fConst253;
	double 	fRec73[3];
	double 	fConst254;
	double 	fRec74[3];
	double 	fConst255;
	double 	fRec75[3];
	double 	fConst256;
	double 	fRec76[3];
	double 	fConst257;
	double 	fRec77[3];
	double 	fConst258;
	double 	fRec78[3];
	double 	fConst259;
	double 	fRec79[3];
	double 	fConst260;
	double 	fRec80[3];
	double 	fConst261;
	double 	fRec81[3];
	double 	fConst262;
	double 	fRec82[3];
	double 	fConst263;
	double 	fRec83[3];
	double 	fConst264;
	double 	fRec84[3];
	double 	fConst265;
	double 	fRec85[3];
	double 	fConst266;
	double 	fRec86[3];
	double 	fConst267;
	double 	fRec87[3];
	double 	fConst268;
	double 	fRec88[3];
	double 	fConst269;
	double 	fRec89[3];
	double 	fConst270;
	double 	fRec90[3];
	double 	fConst271;
	double 	fRec91[3];
	double 	fConst272;
	double 	fRec92[3];
	double 	fConst273;
	double 	fRec93[3];
	double 	fConst274;
	double 	fRec94[3];
	double 	fConst275;
	double 	fRec95[3];
	double 	fConst276;
	double 	fRec96[3];
	double 	fConst277;
	double 	fRec97[3];
	double 	fConst278;
	double 	fRec98[3];
	double 	fConst279;
	double 	fRec99[3];
	double 	fConst280;
	double 	fRec100[3];
	double 	fConst281;
	double 	fRec101[3];
	double 	fConst282;
	double 	fRec102[3];
	double 	fConst283;
	double 	fRec103[3];
	double 	fConst284;
	double 	fRec104[3];
	double 	fConst285;
	double 	fRec105[3];
	double 	fConst286;
	double 	fRec106[3];
	double 	fConst287;
	double 	fRec107[3];
	double 	fConst288;
	double 	fRec108[3];
	double 	fConst289;
	double 	fRec109[3];
	double 	fConst290;
	double 	fRec110[3];
	double 	fConst291;
	double 	fRec111[3];
	double 	fConst292;
	double 	fRec112[3];
	double 	fConst293;
	double 	fRec113[3];
	double 	fConst294;
	double 	fRec114[3];
	double 	fConst295;
	double 	fRec115[3];
	double 	fConst296;
	double 	fRec116[3];
	double 	fConst297;
	double 	fRec117[3];
	double 	fConst298;
	double 	fRec118[3];
	double 	fConst299;
	double 	fRec119[3];
	double 	fConst300;
	double 	fRec120[3];
	double 	fConst301;
	double 	fRec121[3];
	double 	fConst302;
	double 	fRec122[3];
	double 	fConst303;
	double 	fRec123[3];
	double 	fConst304;
	double 	fRec124[3];
	double 	fConst305;
	double 	fRec125[3];
	double 	fConst306;
	double 	fRec126[3];
	double 	fConst307;
	double 	fRec127[3];
	double 	fConst308;
	double 	fRec128[3];
	double 	fConst309;
	double 	fRec129[3];
	double 	fConst310;
	double 	fRec130[3];
	double 	fConst311;
	double 	fRec131[3];
	double 	fConst312;
	double 	fRec132[3];
	double 	fConst313;
	double 	fRec133[3];
	double 	fConst314;
	double 	fRec134[3];
	double 	fConst315;
	double 	fRec135[3];
	double 	fConst316;
	double 	fRec136[3];
	double 	fConst317;
	double 	fRec137[3];
	double 	fConst318;
	double 	fRec138[3];
	double 	fConst319;
	double 	fRec139[3];
	double 	fConst320;
	double 	fRec140[3];
	double 	fConst321;
	double 	fRec141[3];
	double 	fConst322;
	double 	fRec142[3];
	double 	fConst323;
	double 	fRec143[3];
	double 	fConst324;
	double 	fRec144[3];
	double 	fConst325;
	double 	fRec145[3];
	double 	fConst326;
	double 	fRec146[3];
	double 	fConst327;
	double 	fRec147[3];
	double 	fConst328;
	double 	fRec148[3];
	double 	fConst329;
	double 	fRec149[3];
	double 	fConst330;
	double 	fRec150[3];
	double 	fConst331;
	double 	fRec151[3];
	double 	fConst332;
	double 	fRec152[3];
	double 	fConst333;
	double 	fRec153[3];
	double 	fConst334;
	double 	fRec154[3];
	double 	fConst335;
	double 	fRec155[3];
	double 	fConst336;
	double 	fRec156[3];
	double 	fConst337;
	double 	fRec157[3];
	double 	fConst338;
	double 	fRec158[3];
	double 	fConst339;
	double 	fRec159[3];
	double 	fConst340;
	double 	fRec160[3];
	double 	fConst341;
	double 	fRec161[3];
	double 	fConst342;
	double 	fRec162[3];
	double 	fConst343;
	double 	fRec163[3];
	double 	fConst344;
	double 	fRec164[3];
	double 	fConst345;
	double 	fRec165[3];
	double 	fConst346;
	double 	fRec166[3];
	double 	fConst347;
	double 	fRec167[3];
	double 	fConst348;
	double 	fRec168[3];
	double 	fConst349;
	double 	fRec169[3];
	double 	fConst350;
	double 	fRec170[3];
	double 	fConst351;
	double 	fRec171[3];
	double 	fConst352;
	double 	fRec172[3];
	double 	fConst353;
	double 	fRec173[3];
	double 	fConst354;
	double 	fRec174[3];
	double 	fConst355;
	double 	fRec175[3];
	double 	fConst356;
	double 	fRec176[3];
	double 	fConst357;
	double 	fRec177[3];
	double 	fConst358;
	double 	fRec178[3];
	double 	fConst359;
	double 	fRec179[3];
	double 	fConst360;
	double 	fRec180[3];
	double 	fConst361;
	double 	fRec181[3];
	double 	fConst362;
	double 	fRec182[3];
	double 	fConst363;
	double 	fRec183[3];
	double 	fConst364;
	double 	fRec184[3];
	double 	fConst365;
	double 	fRec185[3];
	double 	fConst366;
	double 	fRec186[3];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "tsarWeeded");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("instrument.lib/name", "Faust-STK Tools Library");
		m->declare("instrument.lib/author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("instrument.lib/copyright", "Romain Michon");
		m->declare("instrument.lib/version", "1.0");
		m->declare("instrument.lib/licence", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/version", "1.29");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/copyright", "Julius O. Smith III");
		m->declare("effect.lib/version", "1.33");
		m->declare("effect.lib/license", "STK-4.3");
		m->declare("effect.lib/exciter_name", "Harmonic Exciter");
		m->declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)");
		m->declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("effect.lib/exciter_version", "1.0");
		m->declare("effect.lib/exciter_license", "MIT License (MIT)");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 3; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(251,ftbl0);
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = loadCF(60);
		iConst1 = min(192000, max(1, fSamplingFreq));
		fConst2 = cos((6.283185307179586 * (fConst0 / double(iConst1))));
		fslider0 = 0.99999;
		fConst3 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst0)))));
		fslider1 = 0.99999;
		fentry0 = 0.0002;
		fConst4 = loadX(60);
		fslider2 = 0.9;
		fslider3 = 0.5;
		fslider4 = 0.5;
		fbutton0 = 0.0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider5 = 0.3;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		fConst5 = loadCF(59);
		fConst6 = cos((6.283185307179586 * (fConst5 / double(iConst1))));
		fConst7 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst5)))));
		fConst8 = loadX(59);
		for (int i=0; i<3; i++) fRec5[i] = 0;
		fConst9 = loadCF(58);
		fConst10 = cos((6.283185307179586 * (fConst9 / double(iConst1))));
		fConst11 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst9)))));
		fConst12 = loadX(58);
		for (int i=0; i<3; i++) fRec6[i] = 0;
		fConst13 = loadCF(57);
		fConst14 = cos((6.283185307179586 * (fConst13 / double(iConst1))));
		fConst15 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst13)))));
		fConst16 = loadX(57);
		for (int i=0; i<3; i++) fRec7[i] = 0;
		fConst17 = loadCF(56);
		fConst18 = cos((6.283185307179586 * (fConst17 / double(iConst1))));
		fConst19 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst17)))));
		fConst20 = loadX(56);
		for (int i=0; i<3; i++) fRec8[i] = 0;
		fConst21 = loadCF(55);
		fConst22 = cos((6.283185307179586 * (fConst21 / double(iConst1))));
		fConst23 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst21)))));
		fConst24 = loadX(55);
		for (int i=0; i<3; i++) fRec9[i] = 0;
		fConst25 = loadCF(54);
		fConst26 = cos((6.283185307179586 * (fConst25 / double(iConst1))));
		fConst27 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst25)))));
		fConst28 = loadX(54);
		for (int i=0; i<3; i++) fRec10[i] = 0;
		fConst29 = loadCF(53);
		fConst30 = cos((6.283185307179586 * (fConst29 / double(iConst1))));
		fConst31 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst29)))));
		fConst32 = loadX(53);
		for (int i=0; i<3; i++) fRec11[i] = 0;
		fConst33 = loadCF(52);
		fConst34 = cos((6.283185307179586 * (fConst33 / double(iConst1))));
		fConst35 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst33)))));
		fConst36 = loadX(52);
		for (int i=0; i<3; i++) fRec12[i] = 0;
		fConst37 = loadCF(51);
		fConst38 = cos((6.283185307179586 * (fConst37 / double(iConst1))));
		fConst39 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst37)))));
		fConst40 = loadX(51);
		for (int i=0; i<3; i++) fRec13[i] = 0;
		fConst41 = loadCF(50);
		fConst42 = cos((6.283185307179586 * (fConst41 / double(iConst1))));
		fConst43 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst41)))));
		fConst44 = loadX(50);
		for (int i=0; i<3; i++) fRec14[i] = 0;
		fConst45 = loadCF(49);
		fConst46 = cos((6.283185307179586 * (fConst45 / double(iConst1))));
		fConst47 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst45)))));
		fConst48 = loadX(49);
		for (int i=0; i<3; i++) fRec15[i] = 0;
		fConst49 = loadCF(48);
		fConst50 = cos((6.283185307179586 * (fConst49 / double(iConst1))));
		fConst51 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst49)))));
		fConst52 = loadX(48);
		for (int i=0; i<3; i++) fRec16[i] = 0;
		fConst53 = loadCF(47);
		fConst54 = cos((6.283185307179586 * (fConst53 / double(iConst1))));
		fConst55 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst53)))));
		fConst56 = loadX(47);
		for (int i=0; i<3; i++) fRec17[i] = 0;
		fConst57 = loadCF(46);
		fConst58 = cos((6.283185307179586 * (fConst57 / double(iConst1))));
		fConst59 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst57)))));
		fConst60 = loadX(46);
		for (int i=0; i<3; i++) fRec18[i] = 0;
		fConst61 = loadCF(45);
		fConst62 = cos((6.283185307179586 * (fConst61 / double(iConst1))));
		fConst63 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst61)))));
		fConst64 = loadX(45);
		for (int i=0; i<3; i++) fRec19[i] = 0;
		fConst65 = loadCF(44);
		fConst66 = cos((6.283185307179586 * (fConst65 / double(iConst1))));
		fConst67 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst65)))));
		fConst68 = loadX(44);
		for (int i=0; i<3; i++) fRec20[i] = 0;
		fConst69 = loadCF(43);
		fConst70 = cos((6.283185307179586 * (fConst69 / double(iConst1))));
		fConst71 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst69)))));
		fConst72 = loadX(43);
		for (int i=0; i<3; i++) fRec21[i] = 0;
		fConst73 = loadCF(42);
		fConst74 = cos((6.283185307179586 * (fConst73 / double(iConst1))));
		fConst75 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst73)))));
		fConst76 = loadX(42);
		for (int i=0; i<3; i++) fRec22[i] = 0;
		fConst77 = loadCF(41);
		fConst78 = cos((6.283185307179586 * (fConst77 / double(iConst1))));
		fConst79 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst77)))));
		fConst80 = loadX(41);
		for (int i=0; i<3; i++) fRec23[i] = 0;
		fConst81 = loadCF(40);
		fConst82 = cos((6.283185307179586 * (fConst81 / double(iConst1))));
		fConst83 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst81)))));
		fConst84 = loadX(40);
		for (int i=0; i<3; i++) fRec24[i] = 0;
		fConst85 = loadCF(39);
		fConst86 = cos((6.283185307179586 * (fConst85 / double(iConst1))));
		fConst87 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst85)))));
		fConst88 = loadX(39);
		for (int i=0; i<3; i++) fRec25[i] = 0;
		fConst89 = loadCF(38);
		fConst90 = cos((6.283185307179586 * (fConst89 / double(iConst1))));
		fConst91 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst89)))));
		fConst92 = loadX(38);
		for (int i=0; i<3; i++) fRec26[i] = 0;
		fConst93 = loadCF(37);
		fConst94 = cos((6.283185307179586 * (fConst93 / double(iConst1))));
		fConst95 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst93)))));
		fConst96 = loadX(37);
		for (int i=0; i<3; i++) fRec27[i] = 0;
		fConst97 = loadCF(36);
		fConst98 = cos((6.283185307179586 * (fConst97 / double(iConst1))));
		fConst99 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst97)))));
		fConst100 = loadX(36);
		for (int i=0; i<3; i++) fRec28[i] = 0;
		fConst101 = loadCF(35);
		fConst102 = cos((6.283185307179586 * (fConst101 / double(iConst1))));
		fConst103 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst101)))));
		fConst104 = loadX(35);
		for (int i=0; i<3; i++) fRec29[i] = 0;
		fConst105 = loadCF(34);
		fConst106 = cos((6.283185307179586 * (fConst105 / double(iConst1))));
		fConst107 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst105)))));
		fConst108 = loadX(34);
		for (int i=0; i<3; i++) fRec30[i] = 0;
		fConst109 = loadCF(33);
		fConst110 = cos((6.283185307179586 * (fConst109 / double(iConst1))));
		fConst111 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst109)))));
		fConst112 = loadX(33);
		for (int i=0; i<3; i++) fRec31[i] = 0;
		fConst113 = loadCF(32);
		fConst114 = cos((6.283185307179586 * (fConst113 / double(iConst1))));
		fConst115 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst113)))));
		fConst116 = loadX(32);
		for (int i=0; i<3; i++) fRec32[i] = 0;
		fConst117 = loadCF(31);
		fConst118 = cos((6.283185307179586 * (fConst117 / double(iConst1))));
		fConst119 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst117)))));
		fConst120 = loadX(31);
		for (int i=0; i<3; i++) fRec33[i] = 0;
		fConst121 = loadCF(30);
		fConst122 = cos((6.283185307179586 * (fConst121 / double(iConst1))));
		fConst123 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst121)))));
		fConst124 = loadX(30);
		for (int i=0; i<3; i++) fRec34[i] = 0;
		fConst125 = loadCF(29);
		fConst126 = cos((6.283185307179586 * (fConst125 / double(iConst1))));
		fConst127 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst125)))));
		fConst128 = loadX(29);
		for (int i=0; i<3; i++) fRec35[i] = 0;
		fConst129 = loadCF(28);
		fConst130 = cos((6.283185307179586 * (fConst129 / double(iConst1))));
		fConst131 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst129)))));
		fConst132 = loadX(28);
		for (int i=0; i<3; i++) fRec36[i] = 0;
		fConst133 = loadCF(27);
		fConst134 = cos((6.283185307179586 * (fConst133 / double(iConst1))));
		fConst135 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst133)))));
		fConst136 = loadX(27);
		for (int i=0; i<3; i++) fRec37[i] = 0;
		fConst137 = loadCF(26);
		fConst138 = cos((6.283185307179586 * (fConst137 / double(iConst1))));
		fConst139 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst137)))));
		fConst140 = loadX(26);
		for (int i=0; i<3; i++) fRec38[i] = 0;
		fConst141 = loadCF(25);
		fConst142 = cos((6.283185307179586 * (fConst141 / double(iConst1))));
		fConst143 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst141)))));
		fConst144 = loadX(25);
		for (int i=0; i<3; i++) fRec39[i] = 0;
		fConst145 = loadCF(24);
		fConst146 = cos((6.283185307179586 * (fConst145 / double(iConst1))));
		fConst147 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst145)))));
		fConst148 = loadX(24);
		for (int i=0; i<3; i++) fRec40[i] = 0;
		fConst149 = loadCF(23);
		fConst150 = cos((6.283185307179586 * (fConst149 / double(iConst1))));
		fConst151 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst149)))));
		fConst152 = loadX(23);
		for (int i=0; i<3; i++) fRec41[i] = 0;
		fConst153 = loadCF(22);
		fConst154 = cos((6.283185307179586 * (fConst153 / double(iConst1))));
		fConst155 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst153)))));
		fConst156 = loadX(22);
		for (int i=0; i<3; i++) fRec42[i] = 0;
		fConst157 = loadCF(21);
		fConst158 = cos((6.283185307179586 * (fConst157 / double(iConst1))));
		fConst159 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst157)))));
		fConst160 = loadX(21);
		for (int i=0; i<3; i++) fRec43[i] = 0;
		fConst161 = loadCF(20);
		fConst162 = cos((6.283185307179586 * (fConst161 / double(iConst1))));
		fConst163 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst161)))));
		fConst164 = loadX(20);
		for (int i=0; i<3; i++) fRec44[i] = 0;
		fConst165 = loadCF(19);
		fConst166 = cos((6.283185307179586 * (fConst165 / double(iConst1))));
		fConst167 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst165)))));
		fConst168 = loadX(19);
		for (int i=0; i<3; i++) fRec45[i] = 0;
		fConst169 = loadCF(18);
		fConst170 = cos((6.283185307179586 * (fConst169 / double(iConst1))));
		fConst171 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst169)))));
		fConst172 = loadX(18);
		for (int i=0; i<3; i++) fRec46[i] = 0;
		fConst173 = loadCF(17);
		fConst174 = cos((6.283185307179586 * (fConst173 / double(iConst1))));
		fConst175 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst173)))));
		fConst176 = loadX(17);
		for (int i=0; i<3; i++) fRec47[i] = 0;
		fConst177 = loadCF(16);
		fConst178 = cos((6.283185307179586 * (fConst177 / double(iConst1))));
		fConst179 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst177)))));
		fConst180 = loadX(16);
		for (int i=0; i<3; i++) fRec48[i] = 0;
		fConst181 = loadCF(15);
		fConst182 = cos((6.283185307179586 * (fConst181 / double(iConst1))));
		fConst183 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst181)))));
		fConst184 = loadX(15);
		for (int i=0; i<3; i++) fRec49[i] = 0;
		fConst185 = loadCF(14);
		fConst186 = cos((6.283185307179586 * (fConst185 / double(iConst1))));
		fConst187 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst185)))));
		fConst188 = loadX(14);
		for (int i=0; i<3; i++) fRec50[i] = 0;
		fConst189 = loadCF(13);
		fConst190 = cos((6.283185307179586 * (fConst189 / double(iConst1))));
		fConst191 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst189)))));
		fConst192 = loadX(13);
		for (int i=0; i<3; i++) fRec51[i] = 0;
		fConst193 = loadCF(12);
		fConst194 = cos((6.283185307179586 * (fConst193 / double(iConst1))));
		fConst195 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst193)))));
		fConst196 = loadX(12);
		for (int i=0; i<3; i++) fRec52[i] = 0;
		fConst197 = loadCF(11);
		fConst198 = cos((6.283185307179586 * (fConst197 / double(iConst1))));
		fConst199 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst197)))));
		fConst200 = loadX(11);
		for (int i=0; i<3; i++) fRec53[i] = 0;
		fConst201 = loadCF(10);
		fConst202 = cos((6.283185307179586 * (fConst201 / double(iConst1))));
		fConst203 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst201)))));
		fConst204 = loadX(10);
		for (int i=0; i<3; i++) fRec54[i] = 0;
		fConst205 = loadCF(9);
		fConst206 = cos((6.283185307179586 * (fConst205 / double(iConst1))));
		fConst207 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst205)))));
		fConst208 = loadX(9);
		for (int i=0; i<3; i++) fRec55[i] = 0;
		fConst209 = loadCF(8);
		fConst210 = cos((6.283185307179586 * (fConst209 / double(iConst1))));
		fConst211 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst209)))));
		fConst212 = loadX(8);
		for (int i=0; i<3; i++) fRec56[i] = 0;
		fConst213 = loadCF(7);
		fConst214 = cos((6.283185307179586 * (fConst213 / double(iConst1))));
		fConst215 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst213)))));
		fConst216 = loadX(7);
		for (int i=0; i<3; i++) fRec57[i] = 0;
		fConst217 = loadCF(6);
		fConst218 = cos((6.283185307179586 * (fConst217 / double(iConst1))));
		fConst219 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst217)))));
		fConst220 = loadX(6);
		for (int i=0; i<3; i++) fRec58[i] = 0;
		fConst221 = loadCF(5);
		fConst222 = cos((6.283185307179586 * (fConst221 / double(iConst1))));
		fConst223 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst221)))));
		fConst224 = loadX(5);
		for (int i=0; i<3; i++) fRec59[i] = 0;
		fConst225 = loadCF(4);
		fConst226 = cos((6.283185307179586 * (fConst225 / double(iConst1))));
		fConst227 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst225)))));
		fConst228 = loadX(4);
		for (int i=0; i<3; i++) fRec60[i] = 0;
		fConst229 = loadCF(3);
		fConst230 = cos((6.283185307179586 * (fConst229 / double(iConst1))));
		fConst231 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst229)))));
		fConst232 = loadX(3);
		for (int i=0; i<3; i++) fRec61[i] = 0;
		fConst233 = loadCF(2);
		fConst234 = cos((6.283185307179586 * (fConst233 / double(iConst1))));
		fConst235 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst233)))));
		fConst236 = loadX(2);
		for (int i=0; i<3; i++) fRec62[i] = 0;
		fConst237 = loadCF(0);
		fConst238 = cos((6.283185307179586 * (fConst237 / double(iConst1))));
		fConst239 = (0.01639344262295082 * ((17.31234049066756 * log((0.0022727272727272726 * fConst237))) + 37.69));
		fConst240 = loadX(0);
		for (int i=0; i<3; i++) fRec63[i] = 0;
		fConst241 = loadCF(1);
		fConst242 = cos((6.283185307179586 * (fConst241 / double(iConst1))));
		fConst243 = (0.01639344262295082 * (37.69 + (17.31234049066756 * log((0.0022727272727272726 * fConst241)))));
		fConst244 = loadX(1);
		for (int i=0; i<3; i++) fRec64[i] = 0;
		fConst245 = loadY(60);
		for (int i=0; i<3; i++) fRec65[i] = 0;
		fConst246 = loadY(59);
		for (int i=0; i<3; i++) fRec66[i] = 0;
		fConst247 = loadY(58);
		for (int i=0; i<3; i++) fRec67[i] = 0;
		fConst248 = loadY(57);
		for (int i=0; i<3; i++) fRec68[i] = 0;
		fConst249 = loadY(56);
		for (int i=0; i<3; i++) fRec69[i] = 0;
		fConst250 = loadY(55);
		for (int i=0; i<3; i++) fRec70[i] = 0;
		fConst251 = loadY(54);
		for (int i=0; i<3; i++) fRec71[i] = 0;
		fConst252 = loadY(53);
		for (int i=0; i<3; i++) fRec72[i] = 0;
		fConst253 = loadY(52);
		for (int i=0; i<3; i++) fRec73[i] = 0;
		fConst254 = loadY(51);
		for (int i=0; i<3; i++) fRec74[i] = 0;
		fConst255 = loadY(50);
		for (int i=0; i<3; i++) fRec75[i] = 0;
		fConst256 = loadY(49);
		for (int i=0; i<3; i++) fRec76[i] = 0;
		fConst257 = loadY(48);
		for (int i=0; i<3; i++) fRec77[i] = 0;
		fConst258 = loadY(47);
		for (int i=0; i<3; i++) fRec78[i] = 0;
		fConst259 = loadY(46);
		for (int i=0; i<3; i++) fRec79[i] = 0;
		fConst260 = loadY(45);
		for (int i=0; i<3; i++) fRec80[i] = 0;
		fConst261 = loadY(44);
		for (int i=0; i<3; i++) fRec81[i] = 0;
		fConst262 = loadY(43);
		for (int i=0; i<3; i++) fRec82[i] = 0;
		fConst263 = loadY(42);
		for (int i=0; i<3; i++) fRec83[i] = 0;
		fConst264 = loadY(41);
		for (int i=0; i<3; i++) fRec84[i] = 0;
		fConst265 = loadY(40);
		for (int i=0; i<3; i++) fRec85[i] = 0;
		fConst266 = loadY(39);
		for (int i=0; i<3; i++) fRec86[i] = 0;
		fConst267 = loadY(38);
		for (int i=0; i<3; i++) fRec87[i] = 0;
		fConst268 = loadY(37);
		for (int i=0; i<3; i++) fRec88[i] = 0;
		fConst269 = loadY(36);
		for (int i=0; i<3; i++) fRec89[i] = 0;
		fConst270 = loadY(35);
		for (int i=0; i<3; i++) fRec90[i] = 0;
		fConst271 = loadY(34);
		for (int i=0; i<3; i++) fRec91[i] = 0;
		fConst272 = loadY(33);
		for (int i=0; i<3; i++) fRec92[i] = 0;
		fConst273 = loadY(32);
		for (int i=0; i<3; i++) fRec93[i] = 0;
		fConst274 = loadY(31);
		for (int i=0; i<3; i++) fRec94[i] = 0;
		fConst275 = loadY(30);
		for (int i=0; i<3; i++) fRec95[i] = 0;
		fConst276 = loadY(29);
		for (int i=0; i<3; i++) fRec96[i] = 0;
		fConst277 = loadY(28);
		for (int i=0; i<3; i++) fRec97[i] = 0;
		fConst278 = loadY(27);
		for (int i=0; i<3; i++) fRec98[i] = 0;
		fConst279 = loadY(26);
		for (int i=0; i<3; i++) fRec99[i] = 0;
		fConst280 = loadY(25);
		for (int i=0; i<3; i++) fRec100[i] = 0;
		fConst281 = loadY(24);
		for (int i=0; i<3; i++) fRec101[i] = 0;
		fConst282 = loadY(23);
		for (int i=0; i<3; i++) fRec102[i] = 0;
		fConst283 = loadY(22);
		for (int i=0; i<3; i++) fRec103[i] = 0;
		fConst284 = loadY(21);
		for (int i=0; i<3; i++) fRec104[i] = 0;
		fConst285 = loadY(20);
		for (int i=0; i<3; i++) fRec105[i] = 0;
		fConst286 = loadY(19);
		for (int i=0; i<3; i++) fRec106[i] = 0;
		fConst287 = loadY(18);
		for (int i=0; i<3; i++) fRec107[i] = 0;
		fConst288 = loadY(17);
		for (int i=0; i<3; i++) fRec108[i] = 0;
		fConst289 = loadY(16);
		for (int i=0; i<3; i++) fRec109[i] = 0;
		fConst290 = loadY(15);
		for (int i=0; i<3; i++) fRec110[i] = 0;
		fConst291 = loadY(14);
		for (int i=0; i<3; i++) fRec111[i] = 0;
		fConst292 = loadY(13);
		for (int i=0; i<3; i++) fRec112[i] = 0;
		fConst293 = loadY(12);
		for (int i=0; i<3; i++) fRec113[i] = 0;
		fConst294 = loadY(11);
		for (int i=0; i<3; i++) fRec114[i] = 0;
		fConst295 = loadY(10);
		for (int i=0; i<3; i++) fRec115[i] = 0;
		fConst296 = loadY(9);
		for (int i=0; i<3; i++) fRec116[i] = 0;
		fConst297 = loadY(8);
		for (int i=0; i<3; i++) fRec117[i] = 0;
		fConst298 = loadY(7);
		for (int i=0; i<3; i++) fRec118[i] = 0;
		fConst299 = loadY(6);
		for (int i=0; i<3; i++) fRec119[i] = 0;
		fConst300 = loadY(5);
		for (int i=0; i<3; i++) fRec120[i] = 0;
		fConst301 = loadY(4);
		for (int i=0; i<3; i++) fRec121[i] = 0;
		fConst302 = loadY(3);
		for (int i=0; i<3; i++) fRec122[i] = 0;
		fConst303 = loadY(2);
		for (int i=0; i<3; i++) fRec123[i] = 0;
		fConst304 = loadY(0);
		for (int i=0; i<3; i++) fRec124[i] = 0;
		fConst305 = loadY(1);
		for (int i=0; i<3; i++) fRec125[i] = 0;
		fConst306 = loadZ(60);
		for (int i=0; i<3; i++) fRec126[i] = 0;
		fConst307 = loadZ(59);
		for (int i=0; i<3; i++) fRec127[i] = 0;
		fConst308 = loadZ(58);
		for (int i=0; i<3; i++) fRec128[i] = 0;
		fConst309 = loadZ(57);
		for (int i=0; i<3; i++) fRec129[i] = 0;
		fConst310 = loadZ(56);
		for (int i=0; i<3; i++) fRec130[i] = 0;
		fConst311 = loadZ(55);
		for (int i=0; i<3; i++) fRec131[i] = 0;
		fConst312 = loadZ(54);
		for (int i=0; i<3; i++) fRec132[i] = 0;
		fConst313 = loadZ(53);
		for (int i=0; i<3; i++) fRec133[i] = 0;
		fConst314 = loadZ(52);
		for (int i=0; i<3; i++) fRec134[i] = 0;
		fConst315 = loadZ(51);
		for (int i=0; i<3; i++) fRec135[i] = 0;
		fConst316 = loadZ(50);
		for (int i=0; i<3; i++) fRec136[i] = 0;
		fConst317 = loadZ(49);
		for (int i=0; i<3; i++) fRec137[i] = 0;
		fConst318 = loadZ(48);
		for (int i=0; i<3; i++) fRec138[i] = 0;
		fConst319 = loadZ(47);
		for (int i=0; i<3; i++) fRec139[i] = 0;
		fConst320 = loadZ(46);
		for (int i=0; i<3; i++) fRec140[i] = 0;
		fConst321 = loadZ(45);
		for (int i=0; i<3; i++) fRec141[i] = 0;
		fConst322 = loadZ(44);
		for (int i=0; i<3; i++) fRec142[i] = 0;
		fConst323 = loadZ(43);
		for (int i=0; i<3; i++) fRec143[i] = 0;
		fConst324 = loadZ(42);
		for (int i=0; i<3; i++) fRec144[i] = 0;
		fConst325 = loadZ(41);
		for (int i=0; i<3; i++) fRec145[i] = 0;
		fConst326 = loadZ(40);
		for (int i=0; i<3; i++) fRec146[i] = 0;
		fConst327 = loadZ(39);
		for (int i=0; i<3; i++) fRec147[i] = 0;
		fConst328 = loadZ(38);
		for (int i=0; i<3; i++) fRec148[i] = 0;
		fConst329 = loadZ(37);
		for (int i=0; i<3; i++) fRec149[i] = 0;
		fConst330 = loadZ(36);
		for (int i=0; i<3; i++) fRec150[i] = 0;
		fConst331 = loadZ(35);
		for (int i=0; i<3; i++) fRec151[i] = 0;
		fConst332 = loadZ(34);
		for (int i=0; i<3; i++) fRec152[i] = 0;
		fConst333 = loadZ(33);
		for (int i=0; i<3; i++) fRec153[i] = 0;
		fConst334 = loadZ(32);
		for (int i=0; i<3; i++) fRec154[i] = 0;
		fConst335 = loadZ(31);
		for (int i=0; i<3; i++) fRec155[i] = 0;
		fConst336 = loadZ(30);
		for (int i=0; i<3; i++) fRec156[i] = 0;
		fConst337 = loadZ(29);
		for (int i=0; i<3; i++) fRec157[i] = 0;
		fConst338 = loadZ(28);
		for (int i=0; i<3; i++) fRec158[i] = 0;
		fConst339 = loadZ(27);
		for (int i=0; i<3; i++) fRec159[i] = 0;
		fConst340 = loadZ(26);
		for (int i=0; i<3; i++) fRec160[i] = 0;
		fConst341 = loadZ(25);
		for (int i=0; i<3; i++) fRec161[i] = 0;
		fConst342 = loadZ(24);
		for (int i=0; i<3; i++) fRec162[i] = 0;
		fConst343 = loadZ(23);
		for (int i=0; i<3; i++) fRec163[i] = 0;
		fConst344 = loadZ(22);
		for (int i=0; i<3; i++) fRec164[i] = 0;
		fConst345 = loadZ(21);
		for (int i=0; i<3; i++) fRec165[i] = 0;
		fConst346 = loadZ(20);
		for (int i=0; i<3; i++) fRec166[i] = 0;
		fConst347 = loadZ(19);
		for (int i=0; i<3; i++) fRec167[i] = 0;
		fConst348 = loadZ(18);
		for (int i=0; i<3; i++) fRec168[i] = 0;
		fConst349 = loadZ(17);
		for (int i=0; i<3; i++) fRec169[i] = 0;
		fConst350 = loadZ(16);
		for (int i=0; i<3; i++) fRec170[i] = 0;
		fConst351 = loadZ(15);
		for (int i=0; i<3; i++) fRec171[i] = 0;
		fConst352 = loadZ(14);
		for (int i=0; i<3; i++) fRec172[i] = 0;
		fConst353 = loadZ(13);
		for (int i=0; i<3; i++) fRec173[i] = 0;
		fConst354 = loadZ(12);
		for (int i=0; i<3; i++) fRec174[i] = 0;
		fConst355 = loadZ(11);
		for (int i=0; i<3; i++) fRec175[i] = 0;
		fConst356 = loadZ(10);
		for (int i=0; i<3; i++) fRec176[i] = 0;
		fConst357 = loadZ(9);
		for (int i=0; i<3; i++) fRec177[i] = 0;
		fConst358 = loadZ(8);
		for (int i=0; i<3; i++) fRec178[i] = 0;
		fConst359 = loadZ(7);
		for (int i=0; i<3; i++) fRec179[i] = 0;
		fConst360 = loadZ(6);
		for (int i=0; i<3; i++) fRec180[i] = 0;
		fConst361 = loadZ(5);
		for (int i=0; i<3; i++) fRec181[i] = 0;
		fConst362 = loadZ(4);
		for (int i=0; i<3; i++) fRec182[i] = 0;
		fConst363 = loadZ(3);
		for (int i=0; i<3; i++) fRec183[i] = 0;
		fConst364 = loadZ(2);
		for (int i=0; i<3; i++) fRec184[i] = 0;
		fConst365 = loadZ(0);
		for (int i=0; i<3; i++) fRec185[i] = 0;
		fConst366 = loadZ(1);
		for (int i=0; i<3; i++) fRec186[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->openHorizontalBox("Basic_Parameters");
		interface->declare(&fentry0, "1", "");
		interface->declare(&fentry0, "tooltip", "Gain (value between 0 and 1)");
		interface->addNumEntry("gain", &fentry0, 0.0002, 0.0, 1.0, 0.0001);
		interface->declare(&fbutton0, "1", "");
		interface->declare(&fbutton0, "tooltip", "noteOn = 1, noteOff = 0");
		interface->addButton("gate", &fbutton0);
		interface->closeBox();
		interface->openHorizontalBox("Physical");
		interface->openVerticalBox("Physical_Parameters");
		interface->declare(&fslider1, "2", "");
		interface->declare(&fslider1, "tooltip", "value 0.99997 to 0.999999");
		interface->addHorizontalSlider("hiDamping", &fslider1, 0.99999, 0.99997, 0.999999, 1e-07);
		interface->declare(&fslider4, "2", "");
		interface->declare(&fslider4, "tooltip", "excitation scaling");
		interface->addHorizontalSlider("hiExc", &fslider4, 0.5, 0.0, 1.0, 0.0001);
		interface->declare(&fslider0, "2", "");
		interface->declare(&fslider0, "tooltip", "value 0.99997 to 0.999999");
		interface->addHorizontalSlider("loDamping", &fslider0, 0.99999, 0.99997, 0.999999, 1e-07);
		interface->declare(&fslider3, "2", "");
		interface->declare(&fslider3, "tooltip", "excitation scaling");
		interface->addHorizontalSlider("loExc", &fslider3, 0.5, 0.0, 1.0, 0.0001);
		interface->declare(&fslider5, "2", "");
		interface->declare(&fslider5, "tooltip", "A value between 0 and 1");
		interface->addHorizontalSlider("stickHardness", &fslider5, 0.3, 0.0, 1.0, 0.001);
		interface->declare(&fslider2, "2", "");
		interface->declare(&fslider2, "tooltip", "excitation strength, from exponent of partial amp, a value between 0 and 1, <1 hits low amplitudes harder");
		interface->addHorizontalSlider("whackBoost", &fslider2, 0.9, 0.0, 1.0, 0.0001);
		interface->closeBox();
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = double(fslider0);
		double 	fSlow1 = (double(fslider1) - fSlow0);
		double 	fSlow2 = (fSlow0 + (fConst3 * fSlow1));
		double 	fSlow3 = (fConst2 * (0 - (2 * fSlow2)));
		double 	fSlow4 = faustpower<2>(fSlow2);
		double 	fSlow5 = double(fentry0);
		double 	fSlow6 = double(fslider2);
		double 	fSlow7 = double(fslider3);
		double 	fSlow8 = (double(fslider4) - fSlow7);
		double 	fSlow9 = (fSlow7 + (fConst3 * fSlow8));
		double 	fSlow10 = ((fSlow5 * pow(fConst4,fSlow6)) * fSlow9);
		double 	fSlow11 = double(fbutton0);
		double 	fSlow12 = pow(4,double(fslider5));
		double 	fSlow13 = (62.75 * fSlow12);
		double 	fSlow14 = (0.25 * fSlow12);
		double 	fSlow15 = (fSlow0 + (fConst7 * fSlow1));
		double 	fSlow16 = (fConst6 * (0 - (2 * fSlow15)));
		double 	fSlow17 = faustpower<2>(fSlow15);
		double 	fSlow18 = (fSlow7 + (fConst7 * fSlow8));
		double 	fSlow19 = ((fSlow5 * pow(fConst8,fSlow6)) * fSlow18);
		double 	fSlow20 = (fSlow0 + (fConst11 * fSlow1));
		double 	fSlow21 = (fConst10 * (0 - (2 * fSlow20)));
		double 	fSlow22 = faustpower<2>(fSlow20);
		double 	fSlow23 = (fSlow7 + (fConst11 * fSlow8));
		double 	fSlow24 = ((fSlow5 * pow(fConst12,fSlow6)) * fSlow23);
		double 	fSlow25 = (fSlow0 + (fConst15 * fSlow1));
		double 	fSlow26 = (fConst14 * (0 - (2 * fSlow25)));
		double 	fSlow27 = faustpower<2>(fSlow25);
		double 	fSlow28 = (fSlow7 + (fConst15 * fSlow8));
		double 	fSlow29 = ((fSlow5 * pow(fConst16,fSlow6)) * fSlow28);
		double 	fSlow30 = (fSlow0 + (fConst19 * fSlow1));
		double 	fSlow31 = (fConst18 * (0 - (2 * fSlow30)));
		double 	fSlow32 = faustpower<2>(fSlow30);
		double 	fSlow33 = (fSlow7 + (fConst19 * fSlow8));
		double 	fSlow34 = ((fSlow5 * pow(fConst20,fSlow6)) * fSlow33);
		double 	fSlow35 = (fSlow0 + (fConst23 * fSlow1));
		double 	fSlow36 = (fConst22 * (0 - (2 * fSlow35)));
		double 	fSlow37 = faustpower<2>(fSlow35);
		double 	fSlow38 = (fSlow7 + (fConst23 * fSlow8));
		double 	fSlow39 = ((fSlow5 * pow(fConst24,fSlow6)) * fSlow38);
		double 	fSlow40 = (fSlow0 + (fConst27 * fSlow1));
		double 	fSlow41 = (fConst26 * (0 - (2 * fSlow40)));
		double 	fSlow42 = faustpower<2>(fSlow40);
		double 	fSlow43 = (fSlow7 + (fConst27 * fSlow8));
		double 	fSlow44 = ((fSlow5 * pow(fConst28,fSlow6)) * fSlow43);
		double 	fSlow45 = (fSlow0 + (fConst31 * fSlow1));
		double 	fSlow46 = (fConst30 * (0 - (2 * fSlow45)));
		double 	fSlow47 = faustpower<2>(fSlow45);
		double 	fSlow48 = (fSlow7 + (fConst31 * fSlow8));
		double 	fSlow49 = ((fSlow5 * pow(fConst32,fSlow6)) * fSlow48);
		double 	fSlow50 = (fSlow0 + (fConst35 * fSlow1));
		double 	fSlow51 = (fConst34 * (0 - (2 * fSlow50)));
		double 	fSlow52 = faustpower<2>(fSlow50);
		double 	fSlow53 = (fSlow7 + (fConst35 * fSlow8));
		double 	fSlow54 = ((fSlow5 * pow(fConst36,fSlow6)) * fSlow53);
		double 	fSlow55 = (fSlow0 + (fConst39 * fSlow1));
		double 	fSlow56 = (fConst38 * (0 - (2 * fSlow55)));
		double 	fSlow57 = faustpower<2>(fSlow55);
		double 	fSlow58 = (fSlow7 + (fConst39 * fSlow8));
		double 	fSlow59 = ((fSlow5 * pow(fConst40,fSlow6)) * fSlow58);
		double 	fSlow60 = (fSlow0 + (fConst43 * fSlow1));
		double 	fSlow61 = (fConst42 * (0 - (2 * fSlow60)));
		double 	fSlow62 = faustpower<2>(fSlow60);
		double 	fSlow63 = (fSlow7 + (fConst43 * fSlow8));
		double 	fSlow64 = ((fSlow5 * pow(fConst44,fSlow6)) * fSlow63);
		double 	fSlow65 = (fSlow0 + (fConst47 * fSlow1));
		double 	fSlow66 = (fConst46 * (0 - (2 * fSlow65)));
		double 	fSlow67 = faustpower<2>(fSlow65);
		double 	fSlow68 = (fSlow7 + (fConst47 * fSlow8));
		double 	fSlow69 = ((fSlow5 * pow(fConst48,fSlow6)) * fSlow68);
		double 	fSlow70 = (fSlow0 + (fConst51 * fSlow1));
		double 	fSlow71 = (fConst50 * (0 - (2 * fSlow70)));
		double 	fSlow72 = faustpower<2>(fSlow70);
		double 	fSlow73 = (fSlow7 + (fConst51 * fSlow8));
		double 	fSlow74 = ((fSlow5 * pow(fConst52,fSlow6)) * fSlow73);
		double 	fSlow75 = (fSlow0 + (fConst55 * fSlow1));
		double 	fSlow76 = (fConst54 * (0 - (2 * fSlow75)));
		double 	fSlow77 = faustpower<2>(fSlow75);
		double 	fSlow78 = (fSlow7 + (fConst55 * fSlow8));
		double 	fSlow79 = ((fSlow5 * pow(fConst56,fSlow6)) * fSlow78);
		double 	fSlow80 = (fSlow0 + (fConst59 * fSlow1));
		double 	fSlow81 = (fConst58 * (0 - (2 * fSlow80)));
		double 	fSlow82 = faustpower<2>(fSlow80);
		double 	fSlow83 = (fSlow7 + (fConst59 * fSlow8));
		double 	fSlow84 = ((fSlow5 * pow(fConst60,fSlow6)) * fSlow83);
		double 	fSlow85 = (fSlow0 + (fConst63 * fSlow1));
		double 	fSlow86 = (fConst62 * (0 - (2 * fSlow85)));
		double 	fSlow87 = faustpower<2>(fSlow85);
		double 	fSlow88 = (fSlow7 + (fConst63 * fSlow8));
		double 	fSlow89 = ((fSlow5 * pow(fConst64,fSlow6)) * fSlow88);
		double 	fSlow90 = (fSlow0 + (fConst67 * fSlow1));
		double 	fSlow91 = (fConst66 * (0 - (2 * fSlow90)));
		double 	fSlow92 = faustpower<2>(fSlow90);
		double 	fSlow93 = (fSlow7 + (fConst67 * fSlow8));
		double 	fSlow94 = ((fSlow5 * pow(fConst68,fSlow6)) * fSlow93);
		double 	fSlow95 = (fSlow0 + (fConst71 * fSlow1));
		double 	fSlow96 = (fConst70 * (0 - (2 * fSlow95)));
		double 	fSlow97 = faustpower<2>(fSlow95);
		double 	fSlow98 = (fSlow7 + (fConst71 * fSlow8));
		double 	fSlow99 = ((fSlow5 * pow(fConst72,fSlow6)) * fSlow98);
		double 	fSlow100 = (fSlow0 + (fConst75 * fSlow1));
		double 	fSlow101 = (fConst74 * (0 - (2 * fSlow100)));
		double 	fSlow102 = faustpower<2>(fSlow100);
		double 	fSlow103 = (fSlow7 + (fConst75 * fSlow8));
		double 	fSlow104 = ((fSlow5 * pow(fConst76,fSlow6)) * fSlow103);
		double 	fSlow105 = (fSlow0 + (fConst79 * fSlow1));
		double 	fSlow106 = (fConst78 * (0 - (2 * fSlow105)));
		double 	fSlow107 = faustpower<2>(fSlow105);
		double 	fSlow108 = (fSlow7 + (fConst79 * fSlow8));
		double 	fSlow109 = ((fSlow5 * pow(fConst80,fSlow6)) * fSlow108);
		double 	fSlow110 = (fSlow0 + (fConst83 * fSlow1));
		double 	fSlow111 = (fConst82 * (0 - (2 * fSlow110)));
		double 	fSlow112 = faustpower<2>(fSlow110);
		double 	fSlow113 = (fSlow7 + (fConst83 * fSlow8));
		double 	fSlow114 = ((fSlow5 * pow(fConst84,fSlow6)) * fSlow113);
		double 	fSlow115 = (fSlow0 + (fConst87 * fSlow1));
		double 	fSlow116 = (fConst86 * (0 - (2 * fSlow115)));
		double 	fSlow117 = faustpower<2>(fSlow115);
		double 	fSlow118 = (fSlow7 + (fConst87 * fSlow8));
		double 	fSlow119 = ((fSlow5 * pow(fConst88,fSlow6)) * fSlow118);
		double 	fSlow120 = (fSlow0 + (fConst91 * fSlow1));
		double 	fSlow121 = (fConst90 * (0 - (2 * fSlow120)));
		double 	fSlow122 = faustpower<2>(fSlow120);
		double 	fSlow123 = (fSlow7 + (fConst91 * fSlow8));
		double 	fSlow124 = ((fSlow5 * pow(fConst92,fSlow6)) * fSlow123);
		double 	fSlow125 = (fSlow0 + (fConst95 * fSlow1));
		double 	fSlow126 = (fConst94 * (0 - (2 * fSlow125)));
		double 	fSlow127 = faustpower<2>(fSlow125);
		double 	fSlow128 = (fSlow7 + (fConst95 * fSlow8));
		double 	fSlow129 = ((fSlow5 * pow(fConst96,fSlow6)) * fSlow128);
		double 	fSlow130 = (fSlow0 + (fConst99 * fSlow1));
		double 	fSlow131 = (fConst98 * (0 - (2 * fSlow130)));
		double 	fSlow132 = faustpower<2>(fSlow130);
		double 	fSlow133 = (fSlow7 + (fConst99 * fSlow8));
		double 	fSlow134 = ((fSlow5 * pow(fConst100,fSlow6)) * fSlow133);
		double 	fSlow135 = (fSlow0 + (fConst103 * fSlow1));
		double 	fSlow136 = (fConst102 * (0 - (2 * fSlow135)));
		double 	fSlow137 = faustpower<2>(fSlow135);
		double 	fSlow138 = (fSlow7 + (fConst103 * fSlow8));
		double 	fSlow139 = ((fSlow5 * pow(fConst104,fSlow6)) * fSlow138);
		double 	fSlow140 = (fSlow0 + (fConst107 * fSlow1));
		double 	fSlow141 = (fConst106 * (0 - (2 * fSlow140)));
		double 	fSlow142 = faustpower<2>(fSlow140);
		double 	fSlow143 = (fSlow7 + (fConst107 * fSlow8));
		double 	fSlow144 = ((fSlow5 * pow(fConst108,fSlow6)) * fSlow143);
		double 	fSlow145 = (fSlow0 + (fConst111 * fSlow1));
		double 	fSlow146 = (fConst110 * (0 - (2 * fSlow145)));
		double 	fSlow147 = faustpower<2>(fSlow145);
		double 	fSlow148 = (fSlow7 + (fConst111 * fSlow8));
		double 	fSlow149 = ((fSlow5 * pow(fConst112,fSlow6)) * fSlow148);
		double 	fSlow150 = (fSlow0 + (fConst115 * fSlow1));
		double 	fSlow151 = (fConst114 * (0 - (2 * fSlow150)));
		double 	fSlow152 = faustpower<2>(fSlow150);
		double 	fSlow153 = (fSlow7 + (fConst115 * fSlow8));
		double 	fSlow154 = ((fSlow5 * pow(fConst116,fSlow6)) * fSlow153);
		double 	fSlow155 = (fSlow0 + (fConst119 * fSlow1));
		double 	fSlow156 = (fConst118 * (0 - (2 * fSlow155)));
		double 	fSlow157 = faustpower<2>(fSlow155);
		double 	fSlow158 = (fSlow7 + (fConst119 * fSlow8));
		double 	fSlow159 = ((fSlow5 * pow(fConst120,fSlow6)) * fSlow158);
		double 	fSlow160 = (fSlow0 + (fConst123 * fSlow1));
		double 	fSlow161 = (fConst122 * (0 - (2 * fSlow160)));
		double 	fSlow162 = faustpower<2>(fSlow160);
		double 	fSlow163 = (fSlow7 + (fConst123 * fSlow8));
		double 	fSlow164 = ((fSlow5 * pow(fConst124,fSlow6)) * fSlow163);
		double 	fSlow165 = (fSlow0 + (fConst127 * fSlow1));
		double 	fSlow166 = (fConst126 * (0 - (2 * fSlow165)));
		double 	fSlow167 = faustpower<2>(fSlow165);
		double 	fSlow168 = (fSlow7 + (fConst127 * fSlow8));
		double 	fSlow169 = ((fSlow5 * pow(fConst128,fSlow6)) * fSlow168);
		double 	fSlow170 = (fSlow0 + (fConst131 * fSlow1));
		double 	fSlow171 = (fConst130 * (0 - (2 * fSlow170)));
		double 	fSlow172 = faustpower<2>(fSlow170);
		double 	fSlow173 = (fSlow7 + (fConst131 * fSlow8));
		double 	fSlow174 = ((fSlow5 * pow(fConst132,fSlow6)) * fSlow173);
		double 	fSlow175 = (fSlow0 + (fConst135 * fSlow1));
		double 	fSlow176 = (fConst134 * (0 - (2 * fSlow175)));
		double 	fSlow177 = faustpower<2>(fSlow175);
		double 	fSlow178 = (fSlow7 + (fConst135 * fSlow8));
		double 	fSlow179 = ((fSlow5 * pow(fConst136,fSlow6)) * fSlow178);
		double 	fSlow180 = (fSlow0 + (fConst139 * fSlow1));
		double 	fSlow181 = (fConst138 * (0 - (2 * fSlow180)));
		double 	fSlow182 = faustpower<2>(fSlow180);
		double 	fSlow183 = (fSlow7 + (fConst139 * fSlow8));
		double 	fSlow184 = ((fSlow5 * pow(fConst140,fSlow6)) * fSlow183);
		double 	fSlow185 = (fSlow0 + (fConst143 * fSlow1));
		double 	fSlow186 = (fConst142 * (0 - (2 * fSlow185)));
		double 	fSlow187 = faustpower<2>(fSlow185);
		double 	fSlow188 = (fSlow7 + (fConst143 * fSlow8));
		double 	fSlow189 = ((fSlow5 * pow(fConst144,fSlow6)) * fSlow188);
		double 	fSlow190 = (fSlow0 + (fConst147 * fSlow1));
		double 	fSlow191 = (fConst146 * (0 - (2 * fSlow190)));
		double 	fSlow192 = faustpower<2>(fSlow190);
		double 	fSlow193 = (fSlow7 + (fConst147 * fSlow8));
		double 	fSlow194 = ((fSlow5 * pow(fConst148,fSlow6)) * fSlow193);
		double 	fSlow195 = (fSlow0 + (fConst151 * fSlow1));
		double 	fSlow196 = (fConst150 * (0 - (2 * fSlow195)));
		double 	fSlow197 = faustpower<2>(fSlow195);
		double 	fSlow198 = (fSlow7 + (fConst151 * fSlow8));
		double 	fSlow199 = ((fSlow5 * pow(fConst152,fSlow6)) * fSlow198);
		double 	fSlow200 = (fSlow0 + (fConst155 * fSlow1));
		double 	fSlow201 = (fConst154 * (0 - (2 * fSlow200)));
		double 	fSlow202 = faustpower<2>(fSlow200);
		double 	fSlow203 = (fSlow7 + (fConst155 * fSlow8));
		double 	fSlow204 = ((fSlow5 * pow(fConst156,fSlow6)) * fSlow203);
		double 	fSlow205 = (fSlow0 + (fConst159 * fSlow1));
		double 	fSlow206 = (fConst158 * (0 - (2 * fSlow205)));
		double 	fSlow207 = faustpower<2>(fSlow205);
		double 	fSlow208 = (fSlow7 + (fConst159 * fSlow8));
		double 	fSlow209 = ((fSlow5 * pow(fConst160,fSlow6)) * fSlow208);
		double 	fSlow210 = (fSlow0 + (fConst163 * fSlow1));
		double 	fSlow211 = (fConst162 * (0 - (2 * fSlow210)));
		double 	fSlow212 = faustpower<2>(fSlow210);
		double 	fSlow213 = (fSlow7 + (fConst163 * fSlow8));
		double 	fSlow214 = ((fSlow5 * pow(fConst164,fSlow6)) * fSlow213);
		double 	fSlow215 = (fSlow0 + (fConst167 * fSlow1));
		double 	fSlow216 = (fConst166 * (0 - (2 * fSlow215)));
		double 	fSlow217 = faustpower<2>(fSlow215);
		double 	fSlow218 = (fSlow7 + (fConst167 * fSlow8));
		double 	fSlow219 = ((fSlow5 * pow(fConst168,fSlow6)) * fSlow218);
		double 	fSlow220 = (fSlow0 + (fConst171 * fSlow1));
		double 	fSlow221 = (fConst170 * (0 - (2 * fSlow220)));
		double 	fSlow222 = faustpower<2>(fSlow220);
		double 	fSlow223 = (fSlow7 + (fConst171 * fSlow8));
		double 	fSlow224 = ((fSlow5 * pow(fConst172,fSlow6)) * fSlow223);
		double 	fSlow225 = (fSlow0 + (fConst175 * fSlow1));
		double 	fSlow226 = (fConst174 * (0 - (2 * fSlow225)));
		double 	fSlow227 = faustpower<2>(fSlow225);
		double 	fSlow228 = (fSlow7 + (fConst175 * fSlow8));
		double 	fSlow229 = ((fSlow5 * pow(fConst176,fSlow6)) * fSlow228);
		double 	fSlow230 = (fSlow0 + (fConst179 * fSlow1));
		double 	fSlow231 = (fConst178 * (0 - (2 * fSlow230)));
		double 	fSlow232 = faustpower<2>(fSlow230);
		double 	fSlow233 = (fSlow7 + (fConst179 * fSlow8));
		double 	fSlow234 = ((fSlow5 * pow(fConst180,fSlow6)) * fSlow233);
		double 	fSlow235 = (fSlow0 + (fConst183 * fSlow1));
		double 	fSlow236 = (fConst182 * (0 - (2 * fSlow235)));
		double 	fSlow237 = faustpower<2>(fSlow235);
		double 	fSlow238 = (fSlow7 + (fConst183 * fSlow8));
		double 	fSlow239 = ((fSlow5 * pow(fConst184,fSlow6)) * fSlow238);
		double 	fSlow240 = (fSlow0 + (fConst187 * fSlow1));
		double 	fSlow241 = (fConst186 * (0 - (2 * fSlow240)));
		double 	fSlow242 = faustpower<2>(fSlow240);
		double 	fSlow243 = (fSlow7 + (fConst187 * fSlow8));
		double 	fSlow244 = ((fSlow5 * pow(fConst188,fSlow6)) * fSlow243);
		double 	fSlow245 = (fSlow0 + (fConst191 * fSlow1));
		double 	fSlow246 = (fConst190 * (0 - (2 * fSlow245)));
		double 	fSlow247 = faustpower<2>(fSlow245);
		double 	fSlow248 = (fSlow7 + (fConst191 * fSlow8));
		double 	fSlow249 = ((fSlow5 * pow(fConst192,fSlow6)) * fSlow248);
		double 	fSlow250 = (fSlow0 + (fConst195 * fSlow1));
		double 	fSlow251 = (fConst194 * (0 - (2 * fSlow250)));
		double 	fSlow252 = faustpower<2>(fSlow250);
		double 	fSlow253 = (fSlow7 + (fConst195 * fSlow8));
		double 	fSlow254 = ((fSlow5 * pow(fConst196,fSlow6)) * fSlow253);
		double 	fSlow255 = (fSlow0 + (fConst199 * fSlow1));
		double 	fSlow256 = (fConst198 * (0 - (2 * fSlow255)));
		double 	fSlow257 = faustpower<2>(fSlow255);
		double 	fSlow258 = (fSlow7 + (fConst199 * fSlow8));
		double 	fSlow259 = ((fSlow5 * pow(fConst200,fSlow6)) * fSlow258);
		double 	fSlow260 = (fSlow0 + (fConst203 * fSlow1));
		double 	fSlow261 = (fConst202 * (0 - (2 * fSlow260)));
		double 	fSlow262 = faustpower<2>(fSlow260);
		double 	fSlow263 = (fSlow7 + (fConst203 * fSlow8));
		double 	fSlow264 = ((fSlow5 * pow(fConst204,fSlow6)) * fSlow263);
		double 	fSlow265 = (fSlow0 + (fConst207 * fSlow1));
		double 	fSlow266 = (fConst206 * (0 - (2 * fSlow265)));
		double 	fSlow267 = faustpower<2>(fSlow265);
		double 	fSlow268 = (fSlow7 + (fConst207 * fSlow8));
		double 	fSlow269 = ((fSlow5 * pow(fConst208,fSlow6)) * fSlow268);
		double 	fSlow270 = (fSlow0 + (fConst211 * fSlow1));
		double 	fSlow271 = (fConst210 * (0 - (2 * fSlow270)));
		double 	fSlow272 = faustpower<2>(fSlow270);
		double 	fSlow273 = (fSlow7 + (fConst211 * fSlow8));
		double 	fSlow274 = ((fSlow5 * pow(fConst212,fSlow6)) * fSlow273);
		double 	fSlow275 = (fSlow0 + (fConst215 * fSlow1));
		double 	fSlow276 = (fConst214 * (0 - (2 * fSlow275)));
		double 	fSlow277 = faustpower<2>(fSlow275);
		double 	fSlow278 = (fSlow7 + (fConst215 * fSlow8));
		double 	fSlow279 = ((fSlow5 * pow(fConst216,fSlow6)) * fSlow278);
		double 	fSlow280 = (fSlow0 + (fConst219 * fSlow1));
		double 	fSlow281 = (fConst218 * (0 - (2 * fSlow280)));
		double 	fSlow282 = faustpower<2>(fSlow280);
		double 	fSlow283 = (fSlow7 + (fConst219 * fSlow8));
		double 	fSlow284 = ((fSlow5 * pow(fConst220,fSlow6)) * fSlow283);
		double 	fSlow285 = (fSlow0 + (fConst223 * fSlow1));
		double 	fSlow286 = (fConst222 * (0 - (2 * fSlow285)));
		double 	fSlow287 = faustpower<2>(fSlow285);
		double 	fSlow288 = (fSlow7 + (fConst223 * fSlow8));
		double 	fSlow289 = ((fSlow5 * pow(fConst224,fSlow6)) * fSlow288);
		double 	fSlow290 = (fSlow0 + (fConst227 * fSlow1));
		double 	fSlow291 = (fConst226 * (0 - (2 * fSlow290)));
		double 	fSlow292 = faustpower<2>(fSlow290);
		double 	fSlow293 = (fSlow7 + (fConst227 * fSlow8));
		double 	fSlow294 = ((fSlow5 * pow(fConst228,fSlow6)) * fSlow293);
		double 	fSlow295 = (fSlow0 + (fConst231 * fSlow1));
		double 	fSlow296 = (fConst230 * (0 - (2 * fSlow295)));
		double 	fSlow297 = faustpower<2>(fSlow295);
		double 	fSlow298 = (fSlow7 + (fConst231 * fSlow8));
		double 	fSlow299 = ((fSlow5 * pow(fConst232,fSlow6)) * fSlow298);
		double 	fSlow300 = (fSlow0 + (fConst235 * fSlow1));
		double 	fSlow301 = (fConst234 * (0 - (2 * fSlow300)));
		double 	fSlow302 = faustpower<2>(fSlow300);
		double 	fSlow303 = (fSlow7 + (fConst235 * fSlow8));
		double 	fSlow304 = ((fSlow5 * pow(fConst236,fSlow6)) * fSlow303);
		double 	fSlow305 = (fSlow0 + (fConst239 * fSlow1));
		double 	fSlow306 = (fConst238 * (0 - (2 * fSlow305)));
		double 	fSlow307 = faustpower<2>(fSlow305);
		double 	fSlow308 = (fSlow7 + (fConst239 * fSlow8));
		double 	fSlow309 = ((fSlow5 * pow(fConst240,fSlow6)) * fSlow308);
		double 	fSlow310 = (fSlow0 + (fConst243 * fSlow1));
		double 	fSlow311 = (fConst242 * (0 - (2 * fSlow310)));
		double 	fSlow312 = faustpower<2>(fSlow310);
		double 	fSlow313 = (fSlow7 + (fConst243 * fSlow8));
		double 	fSlow314 = ((fSlow5 * pow(fConst244,fSlow6)) * fSlow313);
		double 	fSlow315 = ((fSlow5 * pow(fConst245,fSlow6)) * fSlow9);
		double 	fSlow316 = ((fSlow5 * pow(fConst246,fSlow6)) * fSlow18);
		double 	fSlow317 = ((fSlow5 * pow(fConst247,fSlow6)) * fSlow23);
		double 	fSlow318 = ((fSlow5 * pow(fConst248,fSlow6)) * fSlow28);
		double 	fSlow319 = ((fSlow5 * pow(fConst249,fSlow6)) * fSlow33);
		double 	fSlow320 = ((fSlow5 * pow(fConst250,fSlow6)) * fSlow38);
		double 	fSlow321 = ((fSlow5 * pow(fConst251,fSlow6)) * fSlow43);
		double 	fSlow322 = ((fSlow5 * pow(fConst252,fSlow6)) * fSlow48);
		double 	fSlow323 = ((fSlow5 * pow(fConst253,fSlow6)) * fSlow53);
		double 	fSlow324 = ((fSlow5 * pow(fConst254,fSlow6)) * fSlow58);
		double 	fSlow325 = ((fSlow5 * pow(fConst255,fSlow6)) * fSlow63);
		double 	fSlow326 = ((fSlow5 * pow(fConst256,fSlow6)) * fSlow68);
		double 	fSlow327 = ((fSlow5 * pow(fConst257,fSlow6)) * fSlow73);
		double 	fSlow328 = ((fSlow5 * pow(fConst258,fSlow6)) * fSlow78);
		double 	fSlow329 = ((fSlow5 * pow(fConst259,fSlow6)) * fSlow83);
		double 	fSlow330 = ((fSlow5 * pow(fConst260,fSlow6)) * fSlow88);
		double 	fSlow331 = ((fSlow5 * pow(fConst261,fSlow6)) * fSlow93);
		double 	fSlow332 = ((fSlow5 * pow(fConst262,fSlow6)) * fSlow98);
		double 	fSlow333 = ((fSlow5 * pow(fConst263,fSlow6)) * fSlow103);
		double 	fSlow334 = ((fSlow5 * pow(fConst264,fSlow6)) * fSlow108);
		double 	fSlow335 = ((fSlow5 * pow(fConst265,fSlow6)) * fSlow113);
		double 	fSlow336 = ((fSlow5 * pow(fConst266,fSlow6)) * fSlow118);
		double 	fSlow337 = ((fSlow5 * pow(fConst267,fSlow6)) * fSlow123);
		double 	fSlow338 = ((fSlow5 * pow(fConst268,fSlow6)) * fSlow128);
		double 	fSlow339 = ((fSlow5 * pow(fConst269,fSlow6)) * fSlow133);
		double 	fSlow340 = ((fSlow5 * pow(fConst270,fSlow6)) * fSlow138);
		double 	fSlow341 = ((fSlow5 * pow(fConst271,fSlow6)) * fSlow143);
		double 	fSlow342 = ((fSlow5 * pow(fConst272,fSlow6)) * fSlow148);
		double 	fSlow343 = ((fSlow5 * pow(fConst273,fSlow6)) * fSlow153);
		double 	fSlow344 = ((fSlow5 * pow(fConst274,fSlow6)) * fSlow158);
		double 	fSlow345 = ((fSlow5 * pow(fConst275,fSlow6)) * fSlow163);
		double 	fSlow346 = ((fSlow5 * pow(fConst276,fSlow6)) * fSlow168);
		double 	fSlow347 = ((fSlow5 * pow(fConst277,fSlow6)) * fSlow173);
		double 	fSlow348 = ((fSlow5 * pow(fConst278,fSlow6)) * fSlow178);
		double 	fSlow349 = ((fSlow5 * pow(fConst279,fSlow6)) * fSlow183);
		double 	fSlow350 = ((fSlow5 * pow(fConst280,fSlow6)) * fSlow188);
		double 	fSlow351 = ((fSlow5 * pow(fConst281,fSlow6)) * fSlow193);
		double 	fSlow352 = ((fSlow5 * pow(fConst282,fSlow6)) * fSlow198);
		double 	fSlow353 = ((fSlow5 * pow(fConst283,fSlow6)) * fSlow203);
		double 	fSlow354 = ((fSlow5 * pow(fConst284,fSlow6)) * fSlow208);
		double 	fSlow355 = ((fSlow5 * pow(fConst285,fSlow6)) * fSlow213);
		double 	fSlow356 = ((fSlow5 * pow(fConst286,fSlow6)) * fSlow218);
		double 	fSlow357 = ((fSlow5 * pow(fConst287,fSlow6)) * fSlow223);
		double 	fSlow358 = ((fSlow5 * pow(fConst288,fSlow6)) * fSlow228);
		double 	fSlow359 = ((fSlow5 * pow(fConst289,fSlow6)) * fSlow233);
		double 	fSlow360 = ((fSlow5 * pow(fConst290,fSlow6)) * fSlow238);
		double 	fSlow361 = ((fSlow5 * pow(fConst291,fSlow6)) * fSlow243);
		double 	fSlow362 = ((fSlow5 * pow(fConst292,fSlow6)) * fSlow248);
		double 	fSlow363 = ((fSlow5 * pow(fConst293,fSlow6)) * fSlow253);
		double 	fSlow364 = ((fSlow5 * pow(fConst294,fSlow6)) * fSlow258);
		double 	fSlow365 = ((fSlow5 * pow(fConst295,fSlow6)) * fSlow263);
		double 	fSlow366 = ((fSlow5 * pow(fConst296,fSlow6)) * fSlow268);
		double 	fSlow367 = ((fSlow5 * pow(fConst297,fSlow6)) * fSlow273);
		double 	fSlow368 = ((fSlow5 * pow(fConst298,fSlow6)) * fSlow278);
		double 	fSlow369 = ((fSlow5 * pow(fConst299,fSlow6)) * fSlow283);
		double 	fSlow370 = ((fSlow5 * pow(fConst300,fSlow6)) * fSlow288);
		double 	fSlow371 = ((fSlow5 * pow(fConst301,fSlow6)) * fSlow293);
		double 	fSlow372 = ((fSlow5 * pow(fConst302,fSlow6)) * fSlow298);
		double 	fSlow373 = ((fSlow5 * pow(fConst303,fSlow6)) * fSlow303);
		double 	fSlow374 = ((fSlow5 * pow(fConst304,fSlow6)) * fSlow308);
		double 	fSlow375 = ((fSlow5 * pow(fConst305,fSlow6)) * fSlow313);
		double 	fSlow376 = ((fSlow5 * pow(fConst306,fSlow6)) * fSlow9);
		double 	fSlow377 = ((fSlow5 * pow(fConst307,fSlow6)) * fSlow18);
		double 	fSlow378 = ((fSlow5 * pow(fConst308,fSlow6)) * fSlow23);
		double 	fSlow379 = ((fSlow5 * pow(fConst309,fSlow6)) * fSlow28);
		double 	fSlow380 = ((fSlow5 * pow(fConst310,fSlow6)) * fSlow33);
		double 	fSlow381 = ((fSlow5 * pow(fConst311,fSlow6)) * fSlow38);
		double 	fSlow382 = ((fSlow5 * pow(fConst312,fSlow6)) * fSlow43);
		double 	fSlow383 = ((fSlow5 * pow(fConst313,fSlow6)) * fSlow48);
		double 	fSlow384 = ((fSlow5 * pow(fConst314,fSlow6)) * fSlow53);
		double 	fSlow385 = ((fSlow5 * pow(fConst315,fSlow6)) * fSlow58);
		double 	fSlow386 = ((fSlow5 * pow(fConst316,fSlow6)) * fSlow63);
		double 	fSlow387 = ((fSlow5 * pow(fConst317,fSlow6)) * fSlow68);
		double 	fSlow388 = ((fSlow5 * pow(fConst318,fSlow6)) * fSlow73);
		double 	fSlow389 = ((fSlow5 * pow(fConst319,fSlow6)) * fSlow78);
		double 	fSlow390 = ((fSlow5 * pow(fConst320,fSlow6)) * fSlow83);
		double 	fSlow391 = ((fSlow5 * pow(fConst321,fSlow6)) * fSlow88);
		double 	fSlow392 = ((fSlow5 * pow(fConst322,fSlow6)) * fSlow93);
		double 	fSlow393 = ((fSlow5 * pow(fConst323,fSlow6)) * fSlow98);
		double 	fSlow394 = ((fSlow5 * pow(fConst324,fSlow6)) * fSlow103);
		double 	fSlow395 = ((fSlow5 * pow(fConst325,fSlow6)) * fSlow108);
		double 	fSlow396 = ((fSlow5 * pow(fConst326,fSlow6)) * fSlow113);
		double 	fSlow397 = ((fSlow5 * pow(fConst327,fSlow6)) * fSlow118);
		double 	fSlow398 = ((fSlow5 * pow(fConst328,fSlow6)) * fSlow123);
		double 	fSlow399 = ((fSlow5 * pow(fConst329,fSlow6)) * fSlow128);
		double 	fSlow400 = ((fSlow5 * pow(fConst330,fSlow6)) * fSlow133);
		double 	fSlow401 = ((fSlow5 * pow(fConst331,fSlow6)) * fSlow138);
		double 	fSlow402 = ((fSlow5 * pow(fConst332,fSlow6)) * fSlow143);
		double 	fSlow403 = ((fSlow5 * pow(fConst333,fSlow6)) * fSlow148);
		double 	fSlow404 = ((fSlow5 * pow(fConst334,fSlow6)) * fSlow153);
		double 	fSlow405 = ((fSlow5 * pow(fConst335,fSlow6)) * fSlow158);
		double 	fSlow406 = ((fSlow5 * pow(fConst336,fSlow6)) * fSlow163);
		double 	fSlow407 = ((fSlow5 * pow(fConst337,fSlow6)) * fSlow168);
		double 	fSlow408 = ((fSlow5 * pow(fConst338,fSlow6)) * fSlow173);
		double 	fSlow409 = ((fSlow5 * pow(fConst339,fSlow6)) * fSlow178);
		double 	fSlow410 = ((fSlow5 * pow(fConst340,fSlow6)) * fSlow183);
		double 	fSlow411 = ((fSlow5 * pow(fConst341,fSlow6)) * fSlow188);
		double 	fSlow412 = ((fSlow5 * pow(fConst342,fSlow6)) * fSlow193);
		double 	fSlow413 = ((fSlow5 * pow(fConst343,fSlow6)) * fSlow198);
		double 	fSlow414 = ((fSlow5 * pow(fConst344,fSlow6)) * fSlow203);
		double 	fSlow415 = ((fSlow5 * pow(fConst345,fSlow6)) * fSlow208);
		double 	fSlow416 = ((fSlow5 * pow(fConst346,fSlow6)) * fSlow213);
		double 	fSlow417 = ((fSlow5 * pow(fConst347,fSlow6)) * fSlow218);
		double 	fSlow418 = ((fSlow5 * pow(fConst348,fSlow6)) * fSlow223);
		double 	fSlow419 = ((fSlow5 * pow(fConst349,fSlow6)) * fSlow228);
		double 	fSlow420 = ((fSlow5 * pow(fConst350,fSlow6)) * fSlow233);
		double 	fSlow421 = ((fSlow5 * pow(fConst351,fSlow6)) * fSlow238);
		double 	fSlow422 = ((fSlow5 * pow(fConst352,fSlow6)) * fSlow243);
		double 	fSlow423 = ((fSlow5 * pow(fConst353,fSlow6)) * fSlow248);
		double 	fSlow424 = ((fSlow5 * pow(fConst354,fSlow6)) * fSlow253);
		double 	fSlow425 = ((fSlow5 * pow(fConst355,fSlow6)) * fSlow258);
		double 	fSlow426 = ((fSlow5 * pow(fConst356,fSlow6)) * fSlow263);
		double 	fSlow427 = ((fSlow5 * pow(fConst357,fSlow6)) * fSlow268);
		double 	fSlow428 = ((fSlow5 * pow(fConst358,fSlow6)) * fSlow273);
		double 	fSlow429 = ((fSlow5 * pow(fConst359,fSlow6)) * fSlow278);
		double 	fSlow430 = ((fSlow5 * pow(fConst360,fSlow6)) * fSlow283);
		double 	fSlow431 = ((fSlow5 * pow(fConst361,fSlow6)) * fSlow288);
		double 	fSlow432 = ((fSlow5 * pow(fConst362,fSlow6)) * fSlow293);
		double 	fSlow433 = ((fSlow5 * pow(fConst363,fSlow6)) * fSlow298);
		double 	fSlow434 = ((fSlow5 * pow(fConst364,fSlow6)) * fSlow303);
		double 	fSlow435 = ((fSlow5 * pow(fConst365,fSlow6)) * fSlow308);
		double 	fSlow436 = ((fSlow5 * pow(fConst366,fSlow6)) * fSlow313);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		for (int i=0; i<count; i++) {
			double fTemp0 = ((double)input0[i] + fSlow11);
			fRec2[0] = (1 + (fTemp0 * fRec2[1]));
			double fTemp1 = (fSlow14 + fRec4[1]);
			fRec4[0] = (fTemp1 - floor(fTemp1));
			fRec1[0] = ((0.09999999999999998 * ((fTemp0 * ((fRec2[0] - 1) < fSlow13)) * ftbl0[int((251.0 * (fTemp0 * fRec4[0])))])) + (0.9 * fRec1[1]));
			fRec0[0] = (0 - (((fSlow3 * fRec0[1]) + (fSlow4 * fRec0[2])) - (fSlow10 * fRec1[0])));
			fRec5[0] = (0 - (((fSlow16 * fRec5[1]) + (fSlow17 * fRec5[2])) - (fSlow19 * fRec1[0])));
			fRec6[0] = (0 - (((fSlow21 * fRec6[1]) + (fSlow22 * fRec6[2])) - (fSlow24 * fRec1[0])));
			fRec7[0] = (0 - (((fSlow26 * fRec7[1]) + (fSlow27 * fRec7[2])) - (fSlow29 * fRec1[0])));
			fRec8[0] = (0 - (((fSlow31 * fRec8[1]) + (fSlow32 * fRec8[2])) - (fSlow34 * fRec1[0])));
			fRec9[0] = (0 - (((fSlow36 * fRec9[1]) + (fSlow37 * fRec9[2])) - (fSlow39 * fRec1[0])));
			fRec10[0] = (0 - (((fSlow41 * fRec10[1]) + (fSlow42 * fRec10[2])) - (fSlow44 * fRec1[0])));
			fRec11[0] = (0 - (((fSlow46 * fRec11[1]) + (fSlow47 * fRec11[2])) - (fSlow49 * fRec1[0])));
			fRec12[0] = (0 - (((fSlow51 * fRec12[1]) + (fSlow52 * fRec12[2])) - (fSlow54 * fRec1[0])));
			fRec13[0] = (0 - (((fSlow56 * fRec13[1]) + (fSlow57 * fRec13[2])) - (fSlow59 * fRec1[0])));
			fRec14[0] = (0 - (((fSlow61 * fRec14[1]) + (fSlow62 * fRec14[2])) - (fSlow64 * fRec1[0])));
			fRec15[0] = (0 - (((fSlow66 * fRec15[1]) + (fSlow67 * fRec15[2])) - (fSlow69 * fRec1[0])));
			fRec16[0] = (0 - (((fSlow71 * fRec16[1]) + (fSlow72 * fRec16[2])) - (fSlow74 * fRec1[0])));
			fRec17[0] = (0 - (((fSlow76 * fRec17[1]) + (fSlow77 * fRec17[2])) - (fSlow79 * fRec1[0])));
			fRec18[0] = (0 - (((fSlow81 * fRec18[1]) + (fSlow82 * fRec18[2])) - (fSlow84 * fRec1[0])));
			fRec19[0] = (0 - (((fSlow86 * fRec19[1]) + (fSlow87 * fRec19[2])) - (fSlow89 * fRec1[0])));
			fRec20[0] = (0 - (((fSlow91 * fRec20[1]) + (fSlow92 * fRec20[2])) - (fSlow94 * fRec1[0])));
			fRec21[0] = (0 - (((fSlow96 * fRec21[1]) + (fSlow97 * fRec21[2])) - (fSlow99 * fRec1[0])));
			fRec22[0] = (0 - (((fSlow101 * fRec22[1]) + (fSlow102 * fRec22[2])) - (fSlow104 * fRec1[0])));
			fRec23[0] = (0 - (((fSlow106 * fRec23[1]) + (fSlow107 * fRec23[2])) - (fSlow109 * fRec1[0])));
			fRec24[0] = (0 - (((fSlow111 * fRec24[1]) + (fSlow112 * fRec24[2])) - (fSlow114 * fRec1[0])));
			fRec25[0] = (0 - (((fSlow116 * fRec25[1]) + (fSlow117 * fRec25[2])) - (fSlow119 * fRec1[0])));
			fRec26[0] = (0 - (((fSlow121 * fRec26[1]) + (fSlow122 * fRec26[2])) - (fSlow124 * fRec1[0])));
			fRec27[0] = (0 - (((fSlow126 * fRec27[1]) + (fSlow127 * fRec27[2])) - (fSlow129 * fRec1[0])));
			fRec28[0] = (0 - (((fSlow131 * fRec28[1]) + (fSlow132 * fRec28[2])) - (fSlow134 * fRec1[0])));
			fRec29[0] = (0 - (((fSlow136 * fRec29[1]) + (fSlow137 * fRec29[2])) - (fSlow139 * fRec1[0])));
			fRec30[0] = (0 - (((fSlow141 * fRec30[1]) + (fSlow142 * fRec30[2])) - (fSlow144 * fRec1[0])));
			fRec31[0] = (0 - (((fSlow146 * fRec31[1]) + (fSlow147 * fRec31[2])) - (fSlow149 * fRec1[0])));
			fRec32[0] = (0 - (((fSlow151 * fRec32[1]) + (fSlow152 * fRec32[2])) - (fSlow154 * fRec1[0])));
			fRec33[0] = (0 - (((fSlow156 * fRec33[1]) + (fSlow157 * fRec33[2])) - (fSlow159 * fRec1[0])));
			fRec34[0] = (0 - (((fSlow161 * fRec34[1]) + (fSlow162 * fRec34[2])) - (fSlow164 * fRec1[0])));
			fRec35[0] = (0 - (((fSlow166 * fRec35[1]) + (fSlow167 * fRec35[2])) - (fSlow169 * fRec1[0])));
			fRec36[0] = (0 - (((fSlow171 * fRec36[1]) + (fSlow172 * fRec36[2])) - (fSlow174 * fRec1[0])));
			fRec37[0] = (0 - (((fSlow176 * fRec37[1]) + (fSlow177 * fRec37[2])) - (fSlow179 * fRec1[0])));
			fRec38[0] = (0 - (((fSlow181 * fRec38[1]) + (fSlow182 * fRec38[2])) - (fSlow184 * fRec1[0])));
			fRec39[0] = (0 - (((fSlow186 * fRec39[1]) + (fSlow187 * fRec39[2])) - (fSlow189 * fRec1[0])));
			fRec40[0] = (0 - (((fSlow191 * fRec40[1]) + (fSlow192 * fRec40[2])) - (fSlow194 * fRec1[0])));
			fRec41[0] = (0 - (((fSlow196 * fRec41[1]) + (fSlow197 * fRec41[2])) - (fSlow199 * fRec1[0])));
			fRec42[0] = (0 - (((fSlow201 * fRec42[1]) + (fSlow202 * fRec42[2])) - (fSlow204 * fRec1[0])));
			fRec43[0] = (0 - (((fSlow206 * fRec43[1]) + (fSlow207 * fRec43[2])) - (fSlow209 * fRec1[0])));
			fRec44[0] = (0 - (((fSlow211 * fRec44[1]) + (fSlow212 * fRec44[2])) - (fSlow214 * fRec1[0])));
			fRec45[0] = (0 - (((fSlow216 * fRec45[1]) + (fSlow217 * fRec45[2])) - (fSlow219 * fRec1[0])));
			fRec46[0] = (0 - (((fSlow221 * fRec46[1]) + (fSlow222 * fRec46[2])) - (fSlow224 * fRec1[0])));
			fRec47[0] = (0 - (((fSlow226 * fRec47[1]) + (fSlow227 * fRec47[2])) - (fSlow229 * fRec1[0])));
			fRec48[0] = (0 - (((fSlow231 * fRec48[1]) + (fSlow232 * fRec48[2])) - (fSlow234 * fRec1[0])));
			fRec49[0] = (0 - (((fSlow236 * fRec49[1]) + (fSlow237 * fRec49[2])) - (fSlow239 * fRec1[0])));
			fRec50[0] = (0 - (((fSlow241 * fRec50[1]) + (fSlow242 * fRec50[2])) - (fSlow244 * fRec1[0])));
			fRec51[0] = (0 - (((fSlow246 * fRec51[1]) + (fSlow247 * fRec51[2])) - (fSlow249 * fRec1[0])));
			fRec52[0] = (0 - (((fSlow251 * fRec52[1]) + (fSlow252 * fRec52[2])) - (fSlow254 * fRec1[0])));
			fRec53[0] = (0 - (((fSlow256 * fRec53[1]) + (fSlow257 * fRec53[2])) - (fSlow259 * fRec1[0])));
			fRec54[0] = (0 - (((fSlow261 * fRec54[1]) + (fSlow262 * fRec54[2])) - (fSlow264 * fRec1[0])));
			fRec55[0] = (0 - (((fSlow266 * fRec55[1]) + (fSlow267 * fRec55[2])) - (fSlow269 * fRec1[0])));
			fRec56[0] = (0 - (((fSlow271 * fRec56[1]) + (fSlow272 * fRec56[2])) - (fSlow274 * fRec1[0])));
			fRec57[0] = (0 - (((fSlow276 * fRec57[1]) + (fSlow277 * fRec57[2])) - (fSlow279 * fRec1[0])));
			fRec58[0] = (0 - (((fSlow281 * fRec58[1]) + (fSlow282 * fRec58[2])) - (fSlow284 * fRec1[0])));
			fRec59[0] = (0 - (((fSlow286 * fRec59[1]) + (fSlow287 * fRec59[2])) - (fSlow289 * fRec1[0])));
			fRec60[0] = (0 - (((fSlow291 * fRec60[1]) + (fSlow292 * fRec60[2])) - (fSlow294 * fRec1[0])));
			fRec61[0] = (0 - (((fSlow296 * fRec61[1]) + (fSlow297 * fRec61[2])) - (fSlow299 * fRec1[0])));
			fRec62[0] = (0 - (((fSlow301 * fRec62[1]) + (fSlow302 * fRec62[2])) - (fSlow304 * fRec1[0])));
			fRec63[0] = (0 - (((fSlow306 * fRec63[1]) + (fSlow307 * fRec63[2])) - (fSlow309 * fRec1[0])));
			fRec64[0] = (0 - (((fSlow311 * fRec64[1]) + (fSlow312 * fRec64[2])) - (fSlow314 * fRec1[0])));
			output0[i] = (FAUSTFLOAT)(fRec0[0] + (fRec5[0] + (fRec6[0] + (fRec7[0] + (fRec8[0] + (fRec9[0] + (fRec10[0] + (fRec11[0] + (fRec12[0] + (fRec13[0] + (fRec14[0] + (fRec15[0] + (fRec16[0] + (fRec17[0] + (fRec18[0] + (fRec19[0] + (fRec20[0] + (fRec21[0] + (fRec22[0] + (fRec23[0] + (fRec24[0] + (fRec25[0] + (fRec26[0] + (fRec27[0] + (fRec28[0] + (fRec29[0] + (fRec30[0] + (fRec31[0] + (fRec32[0] + (fRec33[0] + (fRec34[0] + (fRec35[0] + (fRec36[0] + (fRec37[0] + (fRec38[0] + (fRec39[0] + (fRec40[0] + (fRec41[0] + (fRec42[0] + (fRec43[0] + (fRec44[0] + (fRec45[0] + (fRec46[0] + (fRec47[0] + (fRec48[0] + (fRec49[0] + (fRec50[0] + (fRec51[0] + (fRec52[0] + (fRec53[0] + (fRec54[0] + (fRec55[0] + (fRec56[0] + (fRec57[0] + (fRec58[0] + (fRec59[0] + (fRec60[0] + (fRec61[0] + (fRec62[0] + (fRec63[0] + fRec64[0]))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
			fRec65[0] = (0 - (((fSlow3 * fRec65[1]) + (fSlow4 * fRec65[2])) - (fSlow315 * fRec1[0])));
			fRec66[0] = (0 - (((fSlow16 * fRec66[1]) + (fSlow17 * fRec66[2])) - (fSlow316 * fRec1[0])));
			fRec67[0] = (0 - (((fSlow21 * fRec67[1]) + (fSlow22 * fRec67[2])) - (fSlow317 * fRec1[0])));
			fRec68[0] = (0 - (((fSlow26 * fRec68[1]) + (fSlow27 * fRec68[2])) - (fSlow318 * fRec1[0])));
			fRec69[0] = (0 - (((fSlow31 * fRec69[1]) + (fSlow32 * fRec69[2])) - (fSlow319 * fRec1[0])));
			fRec70[0] = (0 - (((fSlow36 * fRec70[1]) + (fSlow37 * fRec70[2])) - (fSlow320 * fRec1[0])));
			fRec71[0] = (0 - (((fSlow41 * fRec71[1]) + (fSlow42 * fRec71[2])) - (fSlow321 * fRec1[0])));
			fRec72[0] = (0 - (((fSlow46 * fRec72[1]) + (fSlow47 * fRec72[2])) - (fSlow322 * fRec1[0])));
			fRec73[0] = (0 - (((fSlow51 * fRec73[1]) + (fSlow52 * fRec73[2])) - (fSlow323 * fRec1[0])));
			fRec74[0] = (0 - (((fSlow56 * fRec74[1]) + (fSlow57 * fRec74[2])) - (fSlow324 * fRec1[0])));
			fRec75[0] = (0 - (((fSlow62 * fRec75[2]) + (fSlow61 * fRec75[1])) - (fSlow325 * fRec1[0])));
			fRec76[0] = (0 - (((fSlow66 * fRec76[1]) + (fSlow67 * fRec76[2])) - (fSlow326 * fRec1[0])));
			fRec77[0] = (0 - (((fSlow71 * fRec77[1]) + (fSlow72 * fRec77[2])) - (fSlow327 * fRec1[0])));
			fRec78[0] = (0 - (((fSlow76 * fRec78[1]) + (fSlow77 * fRec78[2])) - (fSlow328 * fRec1[0])));
			fRec79[0] = (0 - (((fSlow81 * fRec79[1]) + (fSlow82 * fRec79[2])) - (fSlow329 * fRec1[0])));
			fRec80[0] = (0 - (((fSlow86 * fRec80[1]) + (fSlow87 * fRec80[2])) - (fSlow330 * fRec1[0])));
			fRec81[0] = (0 - (((fSlow91 * fRec81[1]) + (fSlow92 * fRec81[2])) - (fSlow331 * fRec1[0])));
			fRec82[0] = (0 - (((fSlow96 * fRec82[1]) + (fSlow97 * fRec82[2])) - (fSlow332 * fRec1[0])));
			fRec83[0] = (0 - (((fSlow101 * fRec83[1]) + (fSlow102 * fRec83[2])) - (fSlow333 * fRec1[0])));
			fRec84[0] = (0 - (((fSlow106 * fRec84[1]) + (fSlow107 * fRec84[2])) - (fSlow334 * fRec1[0])));
			fRec85[0] = (0 - (((fSlow111 * fRec85[1]) + (fSlow112 * fRec85[2])) - (fSlow335 * fRec1[0])));
			fRec86[0] = (0 - (((fSlow116 * fRec86[1]) + (fSlow117 * fRec86[2])) - (fSlow336 * fRec1[0])));
			fRec87[0] = (0 - (((fSlow121 * fRec87[1]) + (fSlow122 * fRec87[2])) - (fSlow337 * fRec1[0])));
			fRec88[0] = (0 - (((fSlow126 * fRec88[1]) + (fSlow127 * fRec88[2])) - (fSlow338 * fRec1[0])));
			fRec89[0] = (0 - (((fSlow131 * fRec89[1]) + (fSlow132 * fRec89[2])) - (fSlow339 * fRec1[0])));
			fRec90[0] = (0 - (((fSlow136 * fRec90[1]) + (fSlow137 * fRec90[2])) - (fSlow340 * fRec1[0])));
			fRec91[0] = (0 - (((fSlow141 * fRec91[1]) + (fSlow142 * fRec91[2])) - (fSlow341 * fRec1[0])));
			fRec92[0] = (0 - (((fSlow146 * fRec92[1]) + (fSlow147 * fRec92[2])) - (fSlow342 * fRec1[0])));
			fRec93[0] = (0 - (((fSlow151 * fRec93[1]) + (fSlow152 * fRec93[2])) - (fSlow343 * fRec1[0])));
			fRec94[0] = (0 - (((fSlow156 * fRec94[1]) + (fSlow157 * fRec94[2])) - (fSlow344 * fRec1[0])));
			fRec95[0] = (0 - (((fSlow161 * fRec95[1]) + (fSlow162 * fRec95[2])) - (fSlow345 * fRec1[0])));
			fRec96[0] = (0 - (((fSlow166 * fRec96[1]) + (fSlow167 * fRec96[2])) - (fSlow346 * fRec1[0])));
			fRec97[0] = (0 - (((fSlow171 * fRec97[1]) + (fSlow172 * fRec97[2])) - (fSlow347 * fRec1[0])));
			fRec98[0] = (0 - (((fSlow176 * fRec98[1]) + (fSlow177 * fRec98[2])) - (fSlow348 * fRec1[0])));
			fRec99[0] = (0 - (((fSlow181 * fRec99[1]) + (fSlow182 * fRec99[2])) - (fSlow349 * fRec1[0])));
			fRec100[0] = (0 - (((fSlow186 * fRec100[1]) + (fSlow187 * fRec100[2])) - (fSlow350 * fRec1[0])));
			fRec101[0] = (0 - (((fSlow191 * fRec101[1]) + (fSlow192 * fRec101[2])) - (fSlow351 * fRec1[0])));
			fRec102[0] = (0 - (((fSlow196 * fRec102[1]) + (fSlow197 * fRec102[2])) - (fSlow352 * fRec1[0])));
			fRec103[0] = (0 - (((fSlow201 * fRec103[1]) + (fSlow202 * fRec103[2])) - (fSlow353 * fRec1[0])));
			fRec104[0] = (0 - (((fSlow206 * fRec104[1]) + (fSlow207 * fRec104[2])) - (fSlow354 * fRec1[0])));
			fRec105[0] = (0 - (((fSlow211 * fRec105[1]) + (fSlow212 * fRec105[2])) - (fSlow355 * fRec1[0])));
			fRec106[0] = (0 - (((fSlow216 * fRec106[1]) + (fSlow217 * fRec106[2])) - (fSlow356 * fRec1[0])));
			fRec107[0] = (0 - (((fSlow221 * fRec107[1]) + (fSlow222 * fRec107[2])) - (fSlow357 * fRec1[0])));
			fRec108[0] = (0 - (((fSlow226 * fRec108[1]) + (fSlow227 * fRec108[2])) - (fSlow358 * fRec1[0])));
			fRec109[0] = (0 - (((fSlow231 * fRec109[1]) + (fSlow232 * fRec109[2])) - (fSlow359 * fRec1[0])));
			fRec110[0] = (0 - (((fSlow236 * fRec110[1]) + (fSlow237 * fRec110[2])) - (fSlow360 * fRec1[0])));
			fRec111[0] = (0 - (((fSlow241 * fRec111[1]) + (fSlow242 * fRec111[2])) - (fSlow361 * fRec1[0])));
			fRec112[0] = (0 - (((fSlow246 * fRec112[1]) + (fSlow247 * fRec112[2])) - (fSlow362 * fRec1[0])));
			fRec113[0] = (0 - (((fSlow251 * fRec113[1]) + (fSlow252 * fRec113[2])) - (fSlow363 * fRec1[0])));
			fRec114[0] = (0 - (((fSlow256 * fRec114[1]) + (fSlow257 * fRec114[2])) - (fSlow364 * fRec1[0])));
			fRec115[0] = (0 - (((fSlow261 * fRec115[1]) + (fSlow262 * fRec115[2])) - (fSlow365 * fRec1[0])));
			fRec116[0] = (0 - (((fSlow266 * fRec116[1]) + (fSlow267 * fRec116[2])) - (fSlow366 * fRec1[0])));
			fRec117[0] = (0 - (((fSlow271 * fRec117[1]) + (fSlow272 * fRec117[2])) - (fSlow367 * fRec1[0])));
			fRec118[0] = (0 - (((fSlow276 * fRec118[1]) + (fSlow277 * fRec118[2])) - (fSlow368 * fRec1[0])));
			fRec119[0] = (0 - (((fSlow281 * fRec119[1]) + (fSlow282 * fRec119[2])) - (fSlow369 * fRec1[0])));
			fRec120[0] = (0 - (((fSlow286 * fRec120[1]) + (fSlow287 * fRec120[2])) - (fSlow370 * fRec1[0])));
			fRec121[0] = (0 - (((fSlow291 * fRec121[1]) + (fSlow292 * fRec121[2])) - (fSlow371 * fRec1[0])));
			fRec122[0] = (0 - (((fSlow296 * fRec122[1]) + (fSlow297 * fRec122[2])) - (fSlow372 * fRec1[0])));
			fRec123[0] = (0 - (((fSlow301 * fRec123[1]) + (fSlow302 * fRec123[2])) - (fSlow373 * fRec1[0])));
			fRec124[0] = (0 - (((fSlow306 * fRec124[1]) + (fSlow307 * fRec124[2])) - (fSlow374 * fRec1[0])));
			fRec125[0] = (0 - (((fSlow311 * fRec125[1]) + (fSlow312 * fRec125[2])) - (fSlow375 * fRec1[0])));
			output1[i] = (FAUSTFLOAT)(fRec65[0] + (fRec66[0] + (fRec67[0] + (fRec68[0] + (fRec69[0] + (fRec70[0] + (fRec71[0] + (fRec72[0] + (fRec73[0] + (fRec74[0] + (fRec75[0] + (fRec76[0] + (fRec77[0] + (fRec78[0] + (fRec79[0] + (fRec80[0] + (fRec81[0] + (fRec82[0] + (fRec83[0] + (fRec84[0] + (fRec85[0] + (fRec86[0] + (fRec87[0] + (fRec88[0] + (fRec89[0] + (fRec90[0] + (fRec91[0] + (fRec92[0] + (fRec93[0] + (fRec94[0] + (fRec95[0] + (fRec96[0] + (fRec97[0] + (fRec98[0] + (fRec99[0] + (fRec100[0] + (fRec101[0] + (fRec102[0] + (fRec103[0] + (fRec104[0] + (fRec105[0] + (fRec106[0] + (fRec107[0] + (fRec108[0] + (fRec109[0] + (fRec110[0] + (fRec111[0] + (fRec112[0] + (fRec113[0] + (fRec114[0] + (fRec115[0] + (fRec116[0] + (fRec117[0] + (fRec118[0] + (fRec119[0] + (fRec120[0] + (fRec121[0] + (fRec122[0] + (fRec123[0] + (fRec124[0] + fRec125[0]))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
			fRec126[0] = (0 - (((fSlow3 * fRec126[1]) + (fSlow4 * fRec126[2])) - (fSlow376 * fRec1[0])));
			fRec127[0] = (0 - (((fSlow16 * fRec127[1]) + (fSlow17 * fRec127[2])) - (fSlow377 * fRec1[0])));
			fRec128[0] = (0 - (((fSlow21 * fRec128[1]) + (fSlow22 * fRec128[2])) - (fSlow378 * fRec1[0])));
			fRec129[0] = (0 - (((fSlow26 * fRec129[1]) + (fSlow27 * fRec129[2])) - (fSlow379 * fRec1[0])));
			fRec130[0] = (0 - (((fSlow31 * fRec130[1]) + (fSlow32 * fRec130[2])) - (fSlow380 * fRec1[0])));
			fRec131[0] = (0 - (((fSlow36 * fRec131[1]) + (fSlow37 * fRec131[2])) - (fSlow381 * fRec1[0])));
			fRec132[0] = (0 - (((fSlow41 * fRec132[1]) + (fSlow42 * fRec132[2])) - (fSlow382 * fRec1[0])));
			fRec133[0] = (0 - (((fSlow46 * fRec133[1]) + (fSlow47 * fRec133[2])) - (fSlow383 * fRec1[0])));
			fRec134[0] = (0 - (((fSlow51 * fRec134[1]) + (fSlow52 * fRec134[2])) - (fSlow384 * fRec1[0])));
			fRec135[0] = (0 - (((fSlow56 * fRec135[1]) + (fSlow57 * fRec135[2])) - (fSlow385 * fRec1[0])));
			fRec136[0] = (0 - (((fSlow62 * fRec136[2]) + (fSlow61 * fRec136[1])) - (fSlow386 * fRec1[0])));
			fRec137[0] = (0 - (((fSlow66 * fRec137[1]) + (fSlow67 * fRec137[2])) - (fSlow387 * fRec1[0])));
			fRec138[0] = (0 - (((fSlow71 * fRec138[1]) + (fSlow72 * fRec138[2])) - (fSlow388 * fRec1[0])));
			fRec139[0] = (0 - (((fSlow76 * fRec139[1]) + (fSlow77 * fRec139[2])) - (fSlow389 * fRec1[0])));
			fRec140[0] = (0 - (((fSlow81 * fRec140[1]) + (fSlow82 * fRec140[2])) - (fSlow390 * fRec1[0])));
			fRec141[0] = (0 - (((fSlow86 * fRec141[1]) + (fSlow87 * fRec141[2])) - (fSlow391 * fRec1[0])));
			fRec142[0] = (0 - (((fSlow91 * fRec142[1]) + (fSlow92 * fRec142[2])) - (fSlow392 * fRec1[0])));
			fRec143[0] = (0 - (((fSlow96 * fRec143[1]) + (fSlow97 * fRec143[2])) - (fSlow393 * fRec1[0])));
			fRec144[0] = (0 - (((fSlow101 * fRec144[1]) + (fSlow102 * fRec144[2])) - (fSlow394 * fRec1[0])));
			fRec145[0] = (0 - (((fSlow106 * fRec145[1]) + (fSlow107 * fRec145[2])) - (fSlow395 * fRec1[0])));
			fRec146[0] = (0 - (((fSlow111 * fRec146[1]) + (fSlow112 * fRec146[2])) - (fSlow396 * fRec1[0])));
			fRec147[0] = (0 - (((fSlow116 * fRec147[1]) + (fSlow117 * fRec147[2])) - (fSlow397 * fRec1[0])));
			fRec148[0] = (0 - (((fSlow121 * fRec148[1]) + (fSlow122 * fRec148[2])) - (fSlow398 * fRec1[0])));
			fRec149[0] = (0 - (((fSlow126 * fRec149[1]) + (fSlow127 * fRec149[2])) - (fSlow399 * fRec1[0])));
			fRec150[0] = (0 - (((fSlow131 * fRec150[1]) + (fSlow132 * fRec150[2])) - (fSlow400 * fRec1[0])));
			fRec151[0] = (0 - (((fSlow136 * fRec151[1]) + (fSlow137 * fRec151[2])) - (fSlow401 * fRec1[0])));
			fRec152[0] = (0 - (((fSlow141 * fRec152[1]) + (fSlow142 * fRec152[2])) - (fSlow402 * fRec1[0])));
			fRec153[0] = (0 - (((fSlow146 * fRec153[1]) + (fSlow147 * fRec153[2])) - (fSlow403 * fRec1[0])));
			fRec154[0] = (0 - (((fSlow151 * fRec154[1]) + (fSlow152 * fRec154[2])) - (fSlow404 * fRec1[0])));
			fRec155[0] = (0 - (((fSlow156 * fRec155[1]) + (fSlow157 * fRec155[2])) - (fSlow405 * fRec1[0])));
			fRec156[0] = (0 - (((fSlow161 * fRec156[1]) + (fSlow162 * fRec156[2])) - (fSlow406 * fRec1[0])));
			fRec157[0] = (0 - (((fSlow166 * fRec157[1]) + (fSlow167 * fRec157[2])) - (fSlow407 * fRec1[0])));
			fRec158[0] = (0 - (((fSlow171 * fRec158[1]) + (fSlow172 * fRec158[2])) - (fSlow408 * fRec1[0])));
			fRec159[0] = (0 - (((fSlow176 * fRec159[1]) + (fSlow177 * fRec159[2])) - (fSlow409 * fRec1[0])));
			fRec160[0] = (0 - (((fSlow181 * fRec160[1]) + (fSlow182 * fRec160[2])) - (fSlow410 * fRec1[0])));
			fRec161[0] = (0 - (((fSlow186 * fRec161[1]) + (fSlow187 * fRec161[2])) - (fSlow411 * fRec1[0])));
			fRec162[0] = (0 - (((fSlow191 * fRec162[1]) + (fSlow192 * fRec162[2])) - (fSlow412 * fRec1[0])));
			fRec163[0] = (0 - (((fSlow196 * fRec163[1]) + (fSlow197 * fRec163[2])) - (fSlow413 * fRec1[0])));
			fRec164[0] = (0 - (((fSlow201 * fRec164[1]) + (fSlow202 * fRec164[2])) - (fSlow414 * fRec1[0])));
			fRec165[0] = (0 - (((fSlow206 * fRec165[1]) + (fSlow207 * fRec165[2])) - (fSlow415 * fRec1[0])));
			fRec166[0] = (0 - (((fSlow211 * fRec166[1]) + (fSlow212 * fRec166[2])) - (fSlow416 * fRec1[0])));
			fRec167[0] = (0 - (((fSlow216 * fRec167[1]) + (fSlow217 * fRec167[2])) - (fSlow417 * fRec1[0])));
			fRec168[0] = (0 - (((fSlow221 * fRec168[1]) + (fSlow222 * fRec168[2])) - (fSlow418 * fRec1[0])));
			fRec169[0] = (0 - (((fSlow226 * fRec169[1]) + (fSlow227 * fRec169[2])) - (fSlow419 * fRec1[0])));
			fRec170[0] = (0 - (((fSlow231 * fRec170[1]) + (fSlow232 * fRec170[2])) - (fSlow420 * fRec1[0])));
			fRec171[0] = (0 - (((fSlow236 * fRec171[1]) + (fSlow237 * fRec171[2])) - (fSlow421 * fRec1[0])));
			fRec172[0] = (0 - (((fSlow241 * fRec172[1]) + (fSlow242 * fRec172[2])) - (fSlow422 * fRec1[0])));
			fRec173[0] = (0 - (((fSlow246 * fRec173[1]) + (fSlow247 * fRec173[2])) - (fSlow423 * fRec1[0])));
			fRec174[0] = (0 - (((fSlow251 * fRec174[1]) + (fSlow252 * fRec174[2])) - (fSlow424 * fRec1[0])));
			fRec175[0] = (0 - (((fSlow256 * fRec175[1]) + (fSlow257 * fRec175[2])) - (fSlow425 * fRec1[0])));
			fRec176[0] = (0 - (((fSlow261 * fRec176[1]) + (fSlow262 * fRec176[2])) - (fSlow426 * fRec1[0])));
			fRec177[0] = (0 - (((fSlow266 * fRec177[1]) + (fSlow267 * fRec177[2])) - (fSlow427 * fRec1[0])));
			fRec178[0] = (0 - (((fSlow271 * fRec178[1]) + (fSlow272 * fRec178[2])) - (fSlow428 * fRec1[0])));
			fRec179[0] = (0 - (((fSlow276 * fRec179[1]) + (fSlow277 * fRec179[2])) - (fSlow429 * fRec1[0])));
			fRec180[0] = (0 - (((fSlow281 * fRec180[1]) + (fSlow282 * fRec180[2])) - (fSlow430 * fRec1[0])));
			fRec181[0] = (0 - (((fSlow286 * fRec181[1]) + (fSlow287 * fRec181[2])) - (fSlow431 * fRec1[0])));
			fRec182[0] = (0 - (((fSlow291 * fRec182[1]) + (fSlow292 * fRec182[2])) - (fSlow432 * fRec1[0])));
			fRec183[0] = (0 - (((fSlow296 * fRec183[1]) + (fSlow297 * fRec183[2])) - (fSlow433 * fRec1[0])));
			fRec184[0] = (0 - (((fSlow301 * fRec184[1]) + (fSlow302 * fRec184[2])) - (fSlow434 * fRec1[0])));
			fRec185[0] = (0 - (((fSlow306 * fRec185[1]) + (fSlow307 * fRec185[2])) - (fSlow435 * fRec1[0])));
			fRec186[0] = (0 - (((fSlow311 * fRec186[1]) + (fSlow312 * fRec186[2])) - (fSlow436 * fRec1[0])));
			output2[i] = (FAUSTFLOAT)(fRec126[0] + (fRec127[0] + (fRec128[0] + (fRec129[0] + (fRec130[0] + (fRec131[0] + (fRec132[0] + (fRec133[0] + (fRec134[0] + (fRec135[0] + (fRec136[0] + (fRec137[0] + (fRec138[0] + (fRec139[0] + (fRec140[0] + (fRec141[0] + (fRec142[0] + (fRec143[0] + (fRec144[0] + (fRec145[0] + (fRec146[0] + (fRec147[0] + (fRec148[0] + (fRec149[0] + (fRec150[0] + (fRec151[0] + (fRec152[0] + (fRec153[0] + (fRec154[0] + (fRec155[0] + (fRec156[0] + (fRec157[0] + (fRec158[0] + (fRec159[0] + (fRec160[0] + (fRec161[0] + (fRec162[0] + (fRec163[0] + (fRec164[0] + (fRec165[0] + (fRec166[0] + (fRec167[0] + (fRec168[0] + (fRec169[0] + (fRec170[0] + (fRec171[0] + (fRec172[0] + (fRec173[0] + (fRec174[0] + (fRec175[0] + (fRec176[0] + (fRec177[0] + (fRec178[0] + (fRec179[0] + (fRec180[0] + (fRec181[0] + (fRec182[0] + (fRec183[0] + (fRec184[0] + (fRec185[0] + fRec186[0]))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
			// post processing
			fRec186[2] = fRec186[1]; fRec186[1] = fRec186[0];
			fRec185[2] = fRec185[1]; fRec185[1] = fRec185[0];
			fRec184[2] = fRec184[1]; fRec184[1] = fRec184[0];
			fRec183[2] = fRec183[1]; fRec183[1] = fRec183[0];
			fRec182[2] = fRec182[1]; fRec182[1] = fRec182[0];
			fRec181[2] = fRec181[1]; fRec181[1] = fRec181[0];
			fRec180[2] = fRec180[1]; fRec180[1] = fRec180[0];
			fRec179[2] = fRec179[1]; fRec179[1] = fRec179[0];
			fRec178[2] = fRec178[1]; fRec178[1] = fRec178[0];
			fRec177[2] = fRec177[1]; fRec177[1] = fRec177[0];
			fRec176[2] = fRec176[1]; fRec176[1] = fRec176[0];
			fRec175[2] = fRec175[1]; fRec175[1] = fRec175[0];
			fRec174[2] = fRec174[1]; fRec174[1] = fRec174[0];
			fRec173[2] = fRec173[1]; fRec173[1] = fRec173[0];
			fRec172[2] = fRec172[1]; fRec172[1] = fRec172[0];
			fRec171[2] = fRec171[1]; fRec171[1] = fRec171[0];
			fRec170[2] = fRec170[1]; fRec170[1] = fRec170[0];
			fRec169[2] = fRec169[1]; fRec169[1] = fRec169[0];
			fRec168[2] = fRec168[1]; fRec168[1] = fRec168[0];
			fRec167[2] = fRec167[1]; fRec167[1] = fRec167[0];
			fRec166[2] = fRec166[1]; fRec166[1] = fRec166[0];
			fRec165[2] = fRec165[1]; fRec165[1] = fRec165[0];
			fRec164[2] = fRec164[1]; fRec164[1] = fRec164[0];
			fRec163[2] = fRec163[1]; fRec163[1] = fRec163[0];
			fRec162[2] = fRec162[1]; fRec162[1] = fRec162[0];
			fRec161[2] = fRec161[1]; fRec161[1] = fRec161[0];
			fRec160[2] = fRec160[1]; fRec160[1] = fRec160[0];
			fRec159[2] = fRec159[1]; fRec159[1] = fRec159[0];
			fRec158[2] = fRec158[1]; fRec158[1] = fRec158[0];
			fRec157[2] = fRec157[1]; fRec157[1] = fRec157[0];
			fRec156[2] = fRec156[1]; fRec156[1] = fRec156[0];
			fRec155[2] = fRec155[1]; fRec155[1] = fRec155[0];
			fRec154[2] = fRec154[1]; fRec154[1] = fRec154[0];
			fRec153[2] = fRec153[1]; fRec153[1] = fRec153[0];
			fRec152[2] = fRec152[1]; fRec152[1] = fRec152[0];
			fRec151[2] = fRec151[1]; fRec151[1] = fRec151[0];
			fRec150[2] = fRec150[1]; fRec150[1] = fRec150[0];
			fRec149[2] = fRec149[1]; fRec149[1] = fRec149[0];
			fRec148[2] = fRec148[1]; fRec148[1] = fRec148[0];
			fRec147[2] = fRec147[1]; fRec147[1] = fRec147[0];
			fRec146[2] = fRec146[1]; fRec146[1] = fRec146[0];
			fRec145[2] = fRec145[1]; fRec145[1] = fRec145[0];
			fRec144[2] = fRec144[1]; fRec144[1] = fRec144[0];
			fRec143[2] = fRec143[1]; fRec143[1] = fRec143[0];
			fRec142[2] = fRec142[1]; fRec142[1] = fRec142[0];
			fRec141[2] = fRec141[1]; fRec141[1] = fRec141[0];
			fRec140[2] = fRec140[1]; fRec140[1] = fRec140[0];
			fRec139[2] = fRec139[1]; fRec139[1] = fRec139[0];
			fRec138[2] = fRec138[1]; fRec138[1] = fRec138[0];
			fRec137[2] = fRec137[1]; fRec137[1] = fRec137[0];
			fRec136[2] = fRec136[1]; fRec136[1] = fRec136[0];
			fRec135[2] = fRec135[1]; fRec135[1] = fRec135[0];
			fRec134[2] = fRec134[1]; fRec134[1] = fRec134[0];
			fRec133[2] = fRec133[1]; fRec133[1] = fRec133[0];
			fRec132[2] = fRec132[1]; fRec132[1] = fRec132[0];
			fRec131[2] = fRec131[1]; fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1]; fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1]; fRec129[1] = fRec129[0];
			fRec128[2] = fRec128[1]; fRec128[1] = fRec128[0];
			fRec127[2] = fRec127[1]; fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1]; fRec126[1] = fRec126[0];
			fRec125[2] = fRec125[1]; fRec125[1] = fRec125[0];
			fRec124[2] = fRec124[1]; fRec124[1] = fRec124[0];
			fRec123[2] = fRec123[1]; fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1]; fRec122[1] = fRec122[0];
			fRec121[2] = fRec121[1]; fRec121[1] = fRec121[0];
			fRec120[2] = fRec120[1]; fRec120[1] = fRec120[0];
			fRec119[2] = fRec119[1]; fRec119[1] = fRec119[0];
			fRec118[2] = fRec118[1]; fRec118[1] = fRec118[0];
			fRec117[2] = fRec117[1]; fRec117[1] = fRec117[0];
			fRec116[2] = fRec116[1]; fRec116[1] = fRec116[0];
			fRec115[2] = fRec115[1]; fRec115[1] = fRec115[0];
			fRec114[2] = fRec114[1]; fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1]; fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1]; fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1]; fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1]; fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1]; fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1]; fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1]; fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1]; fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1]; fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1]; fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1]; fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1]; fRec102[1] = fRec102[0];
			fRec101[2] = fRec101[1]; fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1]; fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1]; fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1]; fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1]; fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1]; fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1]; fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1]; fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1]; fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1]; fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1]; fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1]; fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1]; fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1]; fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1]; fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1]; fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1]; fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1]; fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1]; fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1]; fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1]; fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1]; fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1]; fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1]; fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1]; fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1]; fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1]; fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1]; fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1]; fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1]; fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1]; fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
		}
	}
};


double 	mydsp::ftbl0[251];

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/


/* Faust code wrapper ------- */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "jpatcher_api.h"
#include <string.h>

#define ASSIST_INLET 	1  		/* should be defined somewhere ?? */
#define ASSIST_OUTLET 	2		/* should be defined somewhere ?? */

#define EXTERNAL_VERSION "0.55"

static const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

class mspUI;

struct Max_Meta1 : Meta
{
    int fCount;
    
    Max_Meta1():fCount(0)
    {}
     
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            fCount++;
        }
    }
};

struct Max_Meta2 : Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};


/*--------------------------------------------------------------------------*/
typedef struct faust
{
    t_pxobject m_ob;
    t_atom *m_seen, *m_want;
    map<string, t_object*> m_output_table;
    short m_where;
    bool m_mute;
    void** args;
    mspUI* dspUI;
    mydsp* dsp;
    char* m_json;
} t_faust;

void *faust_class;

/*--------------------------------------------------------------------------*/
class mspUIObject {

	protected:

		string fLabel;
		FAUSTFLOAT* fZone;

		FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}

	public:

		mspUIObject(const string& label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
		virtual ~mspUIObject() {}

		virtual void setValue(FAUSTFLOAT f) {*fZone = range(0.0,1.0,f);}
        virtual FAUSTFLOAT getValue() { return *fZone; }
		virtual void toString(char* buffer) {}
		virtual string getName() {return fLabel;}
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {

	public:

		mspCheckButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
		virtual ~mspCheckButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "CheckButton(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {

	public:

		mspButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
		virtual ~mspButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Button(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspSlider : public mspUIObject {

	private:

		FAUSTFLOAT fInit;
		FAUSTFLOAT fMin;
		FAUSTFLOAT fMax;
		FAUSTFLOAT fStep;

	public:

		mspSlider(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
			:mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
		virtual ~mspSlider() {}

		void toString(char* buffer)
		{
            stringstream s; 
            s << "Slider(double): " << fLabel << " [init=" << fInit << ":min=" << fMin << ":max=" << fMax << ":step=" << fStep << ":cur=" << *fZone << "]";
            strcpy(buffer, s.str().c_str());
		}

		void setValue(FAUSTFLOAT f) {*fZone = range(fMin,fMax,f);}
};

/*--------------------------------------------------------------------------*/
class mspBargraph : public mspUIObject {
    
    private:
        
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fCurrent;
        
    public:
        
        mspBargraph(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        :mspUIObject(label,zone),fMin(min),fMax(max),fCurrent(*zone) {}
        virtual ~mspBargraph() {}
        
        void toString(char* buffer)
        {
            stringstream s; 
            s << "Bargraph(float): " << fLabel << " [min=" << fMin << ":max=" << fMax << ":cur=" << *fZone << "]";
            strcpy(buffer, s.str().c_str());
        }
        
        virtual FAUSTFLOAT getValue() 
        { 
            if (*fZone != fCurrent) {
                fCurrent = *fZone;
                return fCurrent;
            } else {
                return NAN; 
            }
        }
};

/*--------------------------------------------------------------------------*/

#define MULTI_SIZE  256

class mspUI : public UI
{
	private:

        map<string, mspUIObject*> fUITable1;       // Table using labels
        map<string, mspUIObject*> fUITable2;       // Table using complete path
        map<string, mspUIObject*> fUITable3;       // Table containing bargraph
       
        map<const char*, const char*> fDeclareTable;
        std::vector<std::string> fControlsLevel;
        
        FAUSTFLOAT* fMultiTable[MULTI_SIZE];
        int fMultiIndex;
        int fMultiControl;
        
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        string createLabel(const char* label)
        {
            map<const char*, const char*>::reverse_iterator it;
            if (fDeclareTable.size() > 0) {
                unsigned int i = 0;
                string res = string(label);
                char sep = '[';
                for (it = fDeclareTable.rbegin(); it != fDeclareTable.rend(); it++, i++) {
                    res = res + sep + (*it).first + ":" + (*it).second;
                    sep = ',';
                }
                res += ']';
                fDeclareTable.clear();
                return res;
            } else {
                return string(label);
            }
        }

	public:
    
		typedef map<string, mspUIObject*>::iterator iterator;

		mspUI() 
        {
     		for (int i = 0; i < MULTI_SIZE; i++) {
                fMultiTable[i] = 0;
            }
            fMultiIndex = fMultiControl = 0;
        }
		virtual ~mspUI()
		{
            clear();
   		}
      
		void addButton(const char* label, FAUSTFLOAT* zone) 
        {
            mspUIObject* obj = new mspButton(createLabel(label), zone);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj;
        }
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone) 
        {
            mspUIObject* obj = new mspCheckButton(createLabel(label), zone);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj; 
        }
        
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj; 
        }
        
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj;
        }
        
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {   
            fUITable3[buildPath(label)] = new mspBargraph(createLabel(label), zone, min, max);
            fDeclareTable.clear();
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            fUITable3[buildPath(label)] = new mspBargraph(createLabel(label), zone, min, max);
            fDeclareTable.clear();
        }
    
        void openTabBox(const char* label) {fControlsLevel.push_back(label); fDeclareTable.clear();}
        void openHorizontalBox(const char* label) {fControlsLevel.push_back(label); fDeclareTable.clear();}
        void openVerticalBox(const char* label) {fControlsLevel.push_back(label); fDeclareTable.clear();}
        void closeBox() {fControlsLevel.pop_back(); fDeclareTable.clear();}

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key,"multi") == 0) {
                int index = atoi(val);
                if (index >= 0 && index < MULTI_SIZE) {
                    fMultiTable[index] = zone;
                    fMultiControl++;
                } else {
                    post("Invalid multi index = %d", index);
                }
            }
            
            fDeclareTable[key] = val;
        }
        
        void setMultiValues(FAUSTFLOAT* multi, int buffer_size)
		{
            for (int read = 0; read < buffer_size; read++) {
                int write = (fMultiIndex + read) & (MULTI_SIZE - 1);
                if (fMultiTable[write]) {
                    *fMultiTable[write] = multi[read];
                }
            }
            fMultiIndex += buffer_size;
		}
        
        bool isMulti() { return fMultiControl > 0; }
    
        bool isValue(string name) 
        {
            return (fUITable1.count(name) || fUITable2.count(name));
        }
        bool isOutputValue(string name) 
        {
            return fUITable3.count(name);
        }
        bool isInputValue(string name) 
        {
            return fUITable2.count(name);
        }
        bool setValue(string name, FAUSTFLOAT f)
        {
            if (fUITable1.count(name)) {
                fUITable1[name]->setValue(f);
                return true;
            } else if (fUITable2.count(name)) {
                fUITable2[name]->setValue(f);
                return true;
            } else {
                return false;
            }
        }
		FAUSTFLOAT getOutputValue(string name) { return fUITable3[name]->getValue(); }
          
        iterator begin1()	{ return fUITable1.begin(); }
        iterator end1()		{ return fUITable1.end(); }
        
        iterator begin2()	{ return fUITable2.begin(); }
        iterator end2()		{ return fUITable2.end(); }

        int itemsCount() { return fUITable1.size(); }
        void clear() 
        { 
            iterator it;
            for (it = begin1(); it != end1(); it++) {
                delete (*it).second;
            }
            fUITable1.clear(); 
            fUITable2.clear(); 
        }
};

//--------------------------------------------------------------------------
static bool check_digit(const string& name)
{
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) return true;
    }
    return false;
}

static int count_digit(const string& name)
{
    int count = 0;
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) count++;
    }
    return count;
}

void faust_anything(t_faust* obj, t_symbol* s, short ac, t_atom* av)
{
    bool res = false;
    string name = string((s)->s_name);
     
    if (ac < 0) return;
    
    // Check if no argument is there, consider it is a toggle message for a button
    if (ac == 0 && obj->dspUI->isValue(name)) {
        
        string name = string((s)->s_name);
        float off = 0.0f;
        float on = 1.0f;
        obj->dspUI->setValue(name, off);
        obj->dspUI->setValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        faust_anything(obj, s, 1, av);
        
        return;
    }
    
    // List of values
    if (check_digit(name)) {
        
        int ndigit = 0;
        int pos;
        
        for (pos = name.size() - 1; pos >= 0; pos--) {
            if (isdigit(name[pos]) || name[pos] == ' ') {
                ndigit++;
            } else {
                break;
            }
        }
        pos++;
        
        string prefix = name.substr(0, pos);
        string num_base = name.substr(pos);
        int num = atoi(num_base.c_str());
        
        int i;
        t_atom* ap;
       
        // Increment ap each time to get to the next atom
        for (i = 0, ap = av; i < ac; i++, ap++) {
            float value;
            switch (atom_gettype(ap)) {
                case A_LONG: {
                    value = (float)ap[0].a_w.w_long;
                    break;
                }
                case A_FLOAT:
                    value = ap[0].a_w.w_float;
                    break;
                    
                default:
                    post("Invalid argument in parameter setting"); 
                    return;         
            }
            
            stringstream num_val;
            num_val << num + i;
            char param_name[256];
            
            switch (ndigit - count_digit(num_val.str())) {
                case 0: 
                    sprintf(param_name, "%s%s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 1: 
                    sprintf(param_name, "%s %s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 2: 
                    sprintf(param_name, "%s  %s", prefix.c_str(), num_val.str().c_str());
                    break;
            }
            
            // Try special naming scheme for list of parameters
            res = obj->dspUI->setValue(param_name, value); 
            
            // Otherwise try standard name
            if (!res) {
                res = obj->dspUI->setValue(name, value);
            }
            
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        }
    } else {
        // Standard parameter name
        float value = (av[0].a_type == A_LONG) ? (float)av[0].a_w.w_long : av[0].a_w.w_float;
        res = obj->dspUI->setValue(name, value);
    }
    
    if (!res) {
        post("Unknown parameter : %s", (s)->s_name);
    }
}

/*--------------------------------------------------------------------------*/
void faust_create_jsui(t_faust* x)
{
    t_object *patcher, *box, *obj;
    object_obex_lookup((t_object*)x, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        // Notify JSON
        if (obj && strcmp(object_classname(obj)->s_name, "js") == 0) {
            t_atom json;
            atom_setsym(&json, gensym(x->m_json));
            object_method_typed(obj, gensym("anything"), 1, &json, 0);
            post("Generate UI from JSON...");
        }
    }
        
    // Keep all outputs
    x->m_output_table.clear();
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        t_symbol *scriptingname = jbox_get_varname(obj); // scripting name
        if (scriptingname && x->dspUI->isOutputValue(scriptingname->s_name)) {
            x->m_output_table[scriptingname->s_name] = obj;
        }
    }
}

void faust_update_outputs(t_faust* x)
{
    map<string, t_object*>::iterator it;
    for (it =  x->m_output_table.begin(); it != x->m_output_table.end(); it++) {
        FAUSTFLOAT value = x->dspUI->isOutputValue((*it).first);
        if (value != NAN) {
            t_atom at_value;
            atom_setfloat(&at_value, value);
            object_method_typed((*it).second, gensym("float"), 1, &at_value, 0);
        }
    }
}

/*--------------------------------------------------------------------------*/
void* faust_new(t_symbol* s, short ac, t_atom* av)
{
    t_faust* x = (t_faust*)newobject(faust_class);

    x->m_mute = false;

    x->dsp = new mydsp();
    x->dspUI = new mspUI();

    x->dsp->init(long(sys_getsr()));
    x->dsp->buildUserInterface(x->dspUI);
    
    // Prepare JSON
    JSONUI builder(x->dsp->getNumInputs(), x->dsp->getNumOutputs());
    x->dsp->metadata(&builder);
    x->dsp->buildUserInterface(&builder);
    x->m_json = strdup(builder.JSON().c_str());
    
    int num_input;
    
    if (x->dspUI->isMulti()) {
        num_input = x->dsp->getNumInputs() + 1;
    } else {
        num_input = x->dsp->getNumInputs();
    }
    
    x->args = (void**)calloc((num_input + x->dsp->getNumOutputs()) + 2, sizeof(void*));
    /* Multi in */
    dsp_setup((t_pxobject*)x, num_input);

    /* Multi out */
    for (int i = 0; i< x->dsp->getNumOutputs(); i++) {
        outlet_new((t_pxobject*)x, (char*)"signal");
    }

    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
    
    // send JSON to JS script
    faust_create_jsui(x);
    return x;
}

/*--------------------------------------------------------------------------*/
void faust_dblclick(t_faust* x, long inlet)
{
    post((char*)"------------------");
    for (mspUI::iterator it = x->dspUI->begin1(); it != x->dspUI->end1(); ++it) {
        char param[256];
        it->second->toString(param);
        post(param);
    }
}

/*--------------------------------------------------------------------------*/
//11/13/2015 : faust_assist is actually called at each click in the patcher... to we now use 'faust_dblclick' to display the parameters...
void faust_assist(t_faust* x, void* b, long msg, long a, char* dst)
{
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->dsp->getNumInputs() == 0) {
                sprintf(dst, "(signal) : Unused Input");
            } else {
                sprintf(dst, "(signal) : Audio Input %ld", (a+1));
			}
            /*
			post((char*)"------------------");
			for (mspUI::iterator it = x->dspUI->begin1(); it != x->dspUI->end1(); ++it) {
				char param[256];
				it->second->toString(param);
				post(param);
			}
            */
        } else if (a < x->dsp->getNumInputs()) {
            sprintf(dst, "(signal) : Audio Input %ld", (a+1));
        }
    } else if (msg == ASSIST_OUTLET) {
        sprintf(dst, "(signal) : Audio Output %ld", (a+1));
    }
}

/*--------------------------------------------------------------------------*/
void faust_mute(t_faust* obj, t_symbol* s, short ac, t_atom* at)
{
    if (atom_gettype(at) == A_LONG) {
        obj->m_mute = atom_getlong(at);
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust* x)
{
	dsp_free((t_pxobject*)x);
	if (x->dsp) delete x->dsp;
	if (x->dspUI) delete x->dspUI;
	if (x->args) free(x->args);
    if (x->m_json) free(x->m_json);
}

/*--------------------------------------------------------------------------*/
void faust_perform64(t_faust* x, t_object* dsp64, double** ins, long numins, double** outs, long numouts, long sampleframes, long flags, void* userparam)
{
    AVOIDDENORMALS;
    if (x->m_mute) {
        // Write null buffers to outs
        for (int i = 0; i < numouts; i++) {
             memset(outs[i], 0, sizeof(double) * sampleframes);
        }
    } else {
        if (x->dspUI->isMulti()) {
            x->dspUI->setMultiValues(ins[0], sampleframes);
            x->dsp->compute(sampleframes, ++ins, outs);
        } else {
            x->dsp->compute(sampleframes, ins, outs);
        }
        faust_update_outputs(x);
    }
}

/*--------------------------------------------------------------------------*/
void faust_dsp64(t_faust* x, t_object* dsp64, short* count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, faust_perform64, 0, NULL);
}

/*--------------------------------------------------------------------------*/
extern "C" int main(void)
{
	setup((t_messlist**)&faust_class, (method)faust_new, (method)faust_free,
		(short)sizeof(t_faust), 0L, A_DEFFLOAT, 0);

	dsp* thedsp = new mydsp();
    mspUI dspUI;
	thedsp->buildUserInterface(&dspUI);

    // 03/11/14 : use 'anything' to handle all parameter changes
    addmess((method)faust_anything, (char*)"anything", A_GIMME, 0);
    addmess((method)faust_dsp64, (char*)"dsp64", A_CANT, 0);
    addmess((method)faust_dblclick, (char*)"dblclick", A_CANT, 0);
    addmess((method)faust_assist, (char*)"assist", A_CANT, 0);
    addmess((method)faust_mute, (char*)"mute", A_GIMME, 0);
    dsp_initclass();

    post((char*)"Faust DSP object v%s (sample = 64 bits code = %s)", EXTERNAL_VERSION, getCodeSize());
    post((char*)"Copyright (c) 2012-2015 Grame");
    Max_Meta1 meta1;
    mydsp::metadata(&meta1);
    if (meta1.fCount > 0) {
        Max_Meta2 meta2;
        post("------------------------------");
        mydsp::metadata(&meta2);
        post("------------------------------");
    }
    
    delete(thedsp);
	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/




