#ifndef __aite_h__
#define __aite_h__

#include <math.h>
#include <file.h>

void extractPrimPoint(const int geo, prim; const float currentlength, process)
{
    float targetlength = process*currentlength;
    float diffe = targetlength - currentlength;

    int points[] = primpoints(geo, prim);

    if(diffe > 0)
    {
        vector posA = point(geo, "P", points[-2]);
        vector posB = point(geo, "P", points[-1]);

        for(int i=0; i<len(points); i++)
            removepoint(geo, points[i]);

        vector posC = diffe * normalize(posB-posA) + posB;

        int ptnum = addpoint(geo, posC);

        //addvertex(geo, prim, ptnum);
    }
    else if(diffe < 0)
    {
        vector lastpos = 0;
        float length = 0;
        int cut = 0;

        foreach(int idx; int pt; points)
        {
            vector pos = point(geo, "P", pt);
            if(idx > 0 && !cut)
            {
                float seglength = distance(pos, lastpos);

                if(length+seglength > targetlength)
                {
                    float frac = (targetlength-length)/seglength;

                    vector newpos = lerp(lastpos, pos, frac);

                    int ptnum = addpoint(geo, newpos);
                    setpointattrib(geo,'N',ptnum,normalize(lastpos-pos),'set');
                    setpointattrib(geo,'up',ptnum,{0,1,0},'set');
                    for(int i=0; i<len(points); i++)
                        removepoint(geo, points[i]);

                    //addvertex(geo, prim, ptnum);

                    break;
                }

                length += seglength;
            }

            lastpos = pos;
        }
    }
    else if(diffe == 0){
        for(int i=0; i<len(points)-1; i++)
        removepoint(geo, points[i]);
    }
}

void primTrim(const int geo, prim; const float currentlength, start , end)
{
    
    float startf;
    float endf;
    int removeparr[];
    
    if(start > end){
        startf = end;
        endf = start;
    }else{
        startf = start;
        endf = end;
    }

    float startlength = currentlength * startf;
    float endlength = currentlength * endf;
    float diffs = startlength - currentlength;
    float diffe = endlength - currentlength;

    int points[] = primpoints(geo, prim);

    if(diffe > 0)
    {
        vector posA = point(geo, "P", points[-2]);
        vector posB = point(geo, "P", points[-1]);

        vector posC = diffe * normalize(posB-posA) + posB;

        int ptnum = addpoint(geo, posC);

        addvertex(geo, prim, ptnum);
    }
    else if(diffe < 0)
    {
        vector lastpos = 0;
        float length = 0;
        int cut = 0;

        foreach(int idx; int pt; points)
        {
            vector pos = point(geo, "P", pt);
            if(idx > 0 && !cut)
            {
                float seglength = distance(pos, lastpos);

                if(length+seglength > endlength)
                {
                    float frac = (endlength-length)/seglength;

                    vector newpos = lerp(lastpos, pos, frac);

                    int ptnum = addpoint(geo, newpos);

                    for(int i=idx; i<len(points); i++){
                        push(removeparr,points[i]);
                        //removepoint(geo, points[i]);
                    }

                    addvertex(geo, prim, ptnum);

                    break;
                }

                length += seglength;
            }

            lastpos = pos;
        }
    }
        if(diffs > 0)
    {
        vector posA = point(geo, "P", points[-2]);
        vector posB = point(geo, "P", points[-1]);

        vector posC = diffs * normalize(posB-posA) + posB;

        int ptnum = addpoint(geo, posC);

        addvertex(geo, prim, ptnum);
    }
    else if(diffs < 0)
    {

        vector lastpos = 0;
        float length = 0;
        int cut = 0;
        
        foreach(int idx; int pt; points)
        {
            vector pos = point(geo, "P", pt);
            if(idx > 0 && !cut)
            {
                float seglength = distance(pos, lastpos);

                if(length+seglength > startlength)
                {
                    float frac = (startlength-length)/seglength;

                    vector newpos = lerp(lastpos, pos, frac);

                    setpointattrib(geo, "P", idx-1, newpos, "set");

                    //int ptnum = addpoint(geo, newpos);

                    for(int i = 0; i < idx-1; i++){
                        push(removeparr,points[i]);
                        //removepoint(geo, points[i]);
                    }

                    //addvertex(geo, prim, ptnum);

                    break;
                }

                length += seglength;
            }

            lastpos = pos;
        }

    }

    if(start == 1 && end == 1){
        for(int i=0; i<len(points)-1; i++)
            removepoint(geo, points[i]);
    }

    for(int i=0; i<len(removeparr); i++)
        removepoint(geo, removeparr[i]);
}

#endif
