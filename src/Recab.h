/*
 *  Copyright (C) 2010-2012  Christian Fuchsberger,
 *                           Regents of the University of Michigan
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
////////////////////////////////////////////////////////////////////////
// Recalibrator
//
// by Christian Fuchsberger
//
// - Last modified on June 9th, 2010
//
////////////////////////////////////////////////////////////////////////

#ifndef __RE_CAP_H__
#define __RE_CAP_H__


#include <stdint.h>
#include <string>
// imports from samtools
#include "SamFile.h"
#include "Generic.h"
#include "GenomeSequence.h"
#include "MemoryMapArray.h"
#include "HashErrorModel.h"
#include "Prediction.h"
#include "BaseAsciiMap.h"
#include "BamExecutable.h"

class Recab : public BamExecutable
{
public:
    Recab();
    ~Recab();

    static void recabDescription();
    void description();
    void usage();
    void recabSpecificUsageLine();
    void recabSpecificUsage();
    int execute(int argc, char **argv);

    enum PROC_TYPE {
        ANALYZE,
        UPDATE
    };

    bool processRead(SamRecord& record, PROC_TYPE processtype);
    void modelFitPrediction(const char* outputBase);

    void addRecabSpecificParameters(LongParamContainer& params);

private:
    // quality String
    typedef struct {
        std::string oldq;
        std::string newq;
    } quality_t;

    // conversion table
    static void conversionTable();
    static int nt2idx(char c);
    static int nt2idx2[256];

    void processParams();

    // So external programs can read recab parameters.
    bool myParamsSetup;
    String myRefFile;
    String myDbsnpFile;
    String myQField;  // Quality TAG
    int myBlendedWeight;

    //stats
    uint64_t myBasecounts;
    uint64_t myMappedCount;
    uint64_t myUnMappedCount;
    uint64_t myMappedCountQ;
    uint64_t myBunMappedCount;
    uint64_t myBMappedCount;
    uint64_t myZeroMapQualCount;

    GenomeSequence* myReferenceGenome;
    mmapArrayBool_t myDbSNP;
    HashErrorModel hasherrormodel;
    Prediction prediction;

    // Make this member data so it reuses the string structures everytime
    // rather than constructing new ones every time.
    quality_t myQualityStrings;

};

#endif