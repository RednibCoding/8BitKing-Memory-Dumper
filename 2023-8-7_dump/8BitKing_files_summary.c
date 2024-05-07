// all images are BGRA8888
const char *gaps_filename_803cb7d8[26] = {
    // indexed at 0x801dc2a4
    "okcg2.old", // 32x32 unused, dxdiag.bin in its stead

    "mhg4s.ihg", // 400x192: stacked 400x112 excl "ok" to (288;200), 400x40 "no", 400x40 "yes" to (288;272)
    "zaqrc.olc", // 8x224: stacked 8x112 left to (280;200), right to (688;200) msgbox corners
    "efsui.stc", // 328x192: language stacked 328x32 "fav full" to (360;232)
    "apisa.dlk", // 328x192: language stacked 328x32 "fav remove" to (360;232)

    "appvc.ikb", // 150x214 preview bg to Foldername.ini line 15 centered: (48-(150-144)/2;184-(214-208)/2)

    "mkshc.rcv", // 853x480 search bg; coords at 0x80392280 x y w h char
    "hlink.bvs", // 853x288 search letters sel to (0;144)
    "dxva2.nec", // 853x288 search letters down

    "dism.cef",  // 853x480 start+select bg
    "cca.bvs",   // 256x480 start+select sel top to (0;0)
    "d2d1.hgp",  // 256x480
    "bisrv.nec", // 256x480
    "pwsso.occ", // 256x480
    "gpapi.bvs", // 256x480 start+select sel bottom

    "t2ac.sgf",  // 597x80 slot bg to (256;352)
    "msdmo.gdb", // 597x80 slot sel 1
    "hgcpl.cke", // 597x80
    "gpsvc.bvs", // 597x80
    "ksxbar.ax", // 597x80
    "mfsvr.nkf", // 597x80 slot sel 5

    "wshrm.nec", // 217x37 "yes" to (478;216)
    "igc64.dll", // 217x37 "no"

    "lfsvc.dll", // 597x480: language stacked 597x80 "scaling" to (256;352)
    "werui.ioc", // 597x480: language stacked 597x80 "full screen"
    "bxaor.cke"  // 424x240 to (336;88) !!missing yet drawn in Screen!!
};

// 200x256: 8 stacked 200x32, 5 for select+start + fav, history, search
const char *gaps_filename_ui_labels[6] = {
    "gdoiy.old", // English
    "kdq5g.kep", // Chinese
    "m7t3a.ctl", // Arabic
    "i9q1z.bek", // Russian
    "mmcty.dlk", // Spanish
    "uamca.nec"  // Portuguese
};

// https://nummacway.github.io/gb300/#rom-lists
const char *gaaps_filename_game_lists[10][3] = {
    {
        // Foldername.ini line 4: FF7FAAFF FC
        "rdbui.tax", // English
        "fhcfg.nec", // Chinese
        "nethn.bvs", // Pinyin
    },
    {
        // FF7FFFFF PCE
        "urefs.tax", // English
        "adsnt.nec", // Chinese
        "xvb6c.bvs"  // Pinyin
    },
    {
        // FF7FFF7F GB
        "vdsdc.tax", // English
        "umboa.nec", // Chinese
        "qdvd6.bvs"  // Pinyin
    },
    {
        // FFFF7F7F GBC
        "pnpui.tax", // English
        "wjere.nec", // Chinese
        "mgdel.bvs"  // Pinyin
    },
    {// FFFF7F7F ROMS and line 14: 9 _4_ 5 6 7 8
     "tsmfk.tax",
     "tsmfk.tax",
     "tsmfk.tax"},
    {// 9 4 _5_ 6 7 8
     "Favorites.bin",
     "Favorites.bin",
     "Favorites.bin"},
    {// 9 4 5 _6_ 7 8
     "History.bin",
     "History.bin",
     "History.bin"},
    {// 9 4 5 6 _7_ 8 search
     "None",
     "None",
     "None"},
    {// 9 4 5 6 7 _8_ language
     "None",
     "None",
     "None"},
    {// only _9_ 4 5 6 7 8 total; unused
     "None",
     "None",
     "None"}};

// Foldername.ini line 16: 40x24
const char *gaps_filename_list_indicators[9] = {
    "certlm.msa",   // FF7FAAFF FC
    "djctq.rsd",    // FF7FFFFF PCE
    "fvecpl.ai",    // FF7FFF7F GB
    "htui.kcc",     // FFFF7F7F GBC
    "normidna.bin", // FFFF7F7F ROMS and line 14: 9 _4_ 5 6 7 8
    "dxdiag.bin",   // 9 4 _5_ 6 7 8 fav
    "msgsm.dll",    // 9 4 5 _6_ 7 8 history
    "icm32.dll",    // 9 4 5 6 _7_ 8 search
    "icm32.dll",    // 9 4 5 6 7 _8_ language (unused)
};

// 853x480
const char *gaps_filename_list_bg[9] = {
    // making section 10 unusable
    "urlkp.bva", // FF7FAAFF FC
    "c1eac.pab", // FF7FFFFF PCE
    "fltmc.stc", // FF7FFF7F GB
    "cerop.hld", // FFFF7F7F GBC
    "qasfb.ele", // FFFF7F7F ROMS and line 14: 9 _4_ 5 6 7 8
    "uyhbc.dcf", // 9 4 _5_ 6 7 8 fav
    "lkvax.aeg", // 9 4 5 _6_ 7 8 history
    "lfsvc.dlh", // 9 4 5 6 _7_ 8 search
    "ihdsf.bki"  // 9 4 5 6 7 _8_ language (unused, not present)
};

// 853x160: 4 stacked 853x40 to (0;440) navigation hints
const char *gaps_filename_list_navigation[6] = {
    "nhzgq.old", // English
    "plsjz.kep", // Chinese
    "zlabq.ctl", // Arabic
    "opqjz.bek", // Russian
    "m71az.dlk", // Spanish
    "czqjg.nec"  // Portuguese
};

// 853x480 language selections
const char *gaps_filename_language[6] = {
    "eahsd.old", // English
    "hczwa.kep", // Chinese
    "pl87w.ctl", // Arabic
    "jt5mc.bek", // Russian
    "lbzwq.dlk", // Spanish
    "kxgqi.nec"  // Portuguese
};

// 216x192: stacked 216x48 fav, history, search, language to (318;416)
const char *gaps_filename_section_names[6] = {
    "ahjdl.cpa", // English
    "bkhza.ocb", // Chinese
    "copaw.phc", // Arabic
    "dntq1.bvd", // Russian
    "e9uzb.pae", // Spanish
    "fkna2.hgf"  // Portuguese
};

// 853x480 main menu selection
const char *gaps_filename_main_bg[10] = {
    "deskp.cpa", // FF7FAAFF FC
    "wshom.ocb", // FF7FFFFF PCE
    "fdbil.phc", // FF7FFF7F GB
    "urlka.bvd", // FFFF7F7F GBC
    "c1etl.pae", // FFFF7F7F ROMS and line 14: 9 _4_ 5 6 7 8
    "x86ec.hgf", // 9 4 _5_ 6 7 8 fav
    "spmpm.gdg", // 9 4 5 _6_ 7 8 history
    "sdclt.och", // 9 4 5 6 _7_ 8 search
    "ihdsk.bki", // 9 4 5 6 7 _8_ language
    "fltmc.stj"  // only _9_ 4 5 6 7 8 total; unused, not present
};

// 853x384 to (0;40) indexed from 0x803924d0 with coords at 0x803924a8 x y w h
const char *gaps_filename_lang_overlays[6] = {
    "guyzb.cpa", // English
    "hnjza.ocb", // Chinese
    "ikqbg.phc", // Arabic
    "jnaqp.bvd", // Russian
    "knbsd.pae", // Spanish
    "lnzan.hgf"  // Portuguese
};

// signed 16-bit 21560 samples per second https://vonmillhausen.github.io/sf2000/#sounds
const char *gaps_filename_sounds[7] = {
    "pagefile.sys",
    "swapfile.sys",
    "nyquest.gdb",
    "oldversion.kbe",
    "help.lis",
    "c2fkec.pgt",
    "dpnet.dll"};
