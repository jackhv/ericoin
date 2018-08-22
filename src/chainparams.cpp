// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x5d;
        pchMessageStart[0] = 0xc6;
        pchMessageStart[1] = 0x3e;
        pchMessageStart[2] = 0x5e;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"); //-----
        nDefaultPort = 15565;
        nRPCPort = 15566;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 15);

        //CBlock(hash=00008f7146f61e3ffecf5516e0162c1d41929abf716b9e5856d1b8bf19565bc0, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f3d25089259b0ff0f19620c5c1d1ec441dea39f451412aaa34a1cebe5e557eca, nTime=1534921200, nBits=1f01ffff, nNonce=6023, vtx=1, vchBlockSig=)
        //Coinbase(hash=f3d2508925, nTime=1534921200, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a31455249206e6574776f726b207761732072652d6c61756e63686564206f6e2041756775737420323274682c20323031382e)
        //CTxOut(empty)
        //vMerkleTree: f3d2508925 
        const char* pszTimestamp = "ERI network was re-launched on August 22th, 2018.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1534921200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1; //==
        genesis.nTime    = 1534921200; //-----
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 6023; //-----

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00008f7146f61e3ffecf5516e0162c1d41929abf716b9e5856d1b8bf19565bc0")); //-----
        assert(genesis.hashMerkleRoot == uint256("0xf3d25089259b0ff0f19620c5c1d1ec441dea39f451412aaa34a1cebe5e557eca")); //-----

        vSeeds.push_back(CDNSSeedData("ERIseed1", "seed1.ericoin.co")); //-----

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33); // E
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 18); // 8
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 20000; // two weeks
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0x7b;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 25565;
        nRPCPort = 25566;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7204;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00001e74a346f93f177995121bdb9826fb8e5445163d2e87591f6b01291aae5a"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0xaf;
        pchMessageStart[3] = 0xbf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1529319600;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7204;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 28888;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x00001e74a346f93f177995121bdb9826fb8e5445163d2e87591f6b01291aae5a"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
