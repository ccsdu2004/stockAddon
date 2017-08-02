/**  蜗牛股票分析软件SDK插件借口 
     www.snail007.com
	 www.github/ccsdu2004/stockaddon
	 编译环境x86,win7,Qt4.8.7,msvc2010
*/
#ifndef SNAIL_HOST_H
#define SNAIL_HOST_H
#include <tuple>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVector>

#define SNAIL_ADDON_VERSION "1.0.0"
#define SNAIL_ADDON_VERSION_INT 1000

#if defined(WIN32) || defined(WIN64)
    #ifdef SNAIL_EXPORT
        #define SNAIL_API_EXPORT __declspec(dllexport)
    #else
        #define SNAIP_API_IMPORT __declspec(dllimport)
    #endif
#else
    #error 系统不支持
#endif

typedef QVector<std::tuple<bool,float,float,float,float>> CalcData;

class StockImpl;

//日周月线只保证code,start,low,top,current和tradeVolume有数据
//获取股票数据只保证code,name,area,listDate,outstanding,totals有数据
struct Stock
{
    QString code;
	QString name;
	QString area;

	int score;

	unsigned int buy[5];
	unsigned int sale[5];

	QString industry;

	float turnover;
	float tradeVolume;
	float tradeCapital;
	
	float privClose;
	float start;
	float top;
	float low;
	float current;
	float increase;
	float offset;

	float ma5,v_ma5;
	float ma10,v_ma10;
	float ma20,v_ma20;

	QString state;
	QString date;
	QString timeToMarket;
	QString time;
	float p1;
	float p2;

	int outstanding,totals;
	float pe,totalAssets,liquidAssets,fixedAssets,reserved,reservedPerShare,esp,bvps,pb,undp,perundp,rev,profit,gpr,npr;
	int holders;

	bool flag;
	QMap<int,QStringList> desc;
	QString type;
	QString jd;
	QString dp;

	float var;
	StockImpl* impl;

	Stock()
	{
		memset(buy,0,5*sizeof(unsigned int));
		memset(sale,0,5*sizeof(unsigned int));

		score = 0;

		turnover = 0.0;
		tradeVolume = 0.0;
	
		privClose = 0.0;
		start = 0.0;
		top = 0.0;
		low = 0.0;
		current = 0.0;
		increase = 0.0;
		offset = 0.0;

		ma5 = 0.0f;
		ma10 = 0.0f;
		ma20 = 0.0f;

		v_ma5 = 0.0f;
		v_ma10 = 0.0f;
		v_ma20 = 0.0f;

		p1 = 0.0;
		p2 = 0.0;

		outstanding = totals = 0;
		pe = totalAssets = liquidAssets = fixedAssets = reserved = reservedPerShare = esp = bvps = pb = undp = perundp = 
			rev = profit = gpr = npr = 0.0f;
		holders = 0;
		flag = false;
		var = 0.0f;
		impl = nullptr;
	};
};

struct StockIndicator
{
	virtual void clear() = 0;
	virtual std::tuple<bool,float,float,float,float> update(const Stock& stock,bool log = false) = 0;
	virtual std::tuple<bool,float,float,float,float> simulate(const Stock& stock,bool log = false) = 0;
};

struct SnailAddon
{
	virtual ~SnailAddon(){}
	virtual void destroy() = 0;
    virtual const QString maker()const = 0;
	virtual const QString version()const = 0;
	virtual const QString description()const = 0;
    virtual void onRecevied(const QVector<Stock>& list,const CalcData& d1,const CalcData& d2,const CalcData& d3,const CalcData& d4,const CalcData& d5,const CalcData& d6) = 0;	
};

struct SnailAddonHost
{
	virtual const QString version()const = 0;
	virtual QMap<QString,Stock> getStockList()const = 0;

	static const int TAG_Indicator_Macd = 0;
	static const int TAG_Indicator_Ma   = 1;
	static const int TAG_Indicator_Boll = 2;
	static const int TAG_Indicator_Kdj  = 3;
	static const int TAG_Indicator_VolMa = 4;
	virtual StockIndicator* createIndicator(int id,int a,int b,int c) = 0;

	static const int TAG_XuRiDongSheng = 0;
	static const int TAG_HongSanBing = 1;
	static const int TAG_YangTunYin = 2;
	static const int TAG_DuoFangPao = 3;
	static const int TAG_QingChenZhiXing = 4;
	static const int TAG_ChuanCi = 5;
	static const int TAG_PingTouPingDi = 6;
	static const int TAG_ShangShengSanFa = 7;
	static const int TAG_SanYangKaiTai = 8;
	static const int TAG_ChuiZiZhiDie = 9;
	static const int TAG_DaoChuiTou = 10;
    static const int TAG_KanZhangMuZi = 11;

	static const int TAG_YinTunYang = 20;
	static const int TAG_QinPenDaYu = 21;
	static const int TAG_WuYunGaiDing = 22;
	static const int TAG_ZhangShiJinTou = 23;
	static const int TAG_KongFangPao = 24;
	static const int TAG_HuangHunZhiXing = 25;
	static const int TAG_XiaJiangSanFa = 26;
	static const int TAG_HeiSanBing = 27;
	static const int TAG_YangYunShiZi = 28;
	static const int TAG_ShuangFeiWuYa = 29;
	static const int TAG_DiaoJing = 30;
	static const int TAG_LiuXing = 31;
	static const int TAG_KanDieMuZi = 32;	
	virtual bool isThisK(int id,const QVector<Stock>& list) = 0;

	//static const int TAG_Algo_Exe_K_Daily = 0;
	//virtual void execute(int flag) = 0;
	virtual void append(const QString& code,const std::tuple<QString,float>& buy,const std::tuple<QString,float>& sale) = 0;
};

//插件符号
//extern "C" SNAIL_API_EXPORT SnailAddon* get_snail_interface(SnailAddonHost* host,int flag);

#endif 