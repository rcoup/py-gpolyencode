#ifndef GPOLYENCODER_H_
#define GPOLYENCODER_H_

#include <vector>
#include <string>
#include <cmath>
#include <memory>

class GPolyEncoder {

private:
    int numLevels;
    int zoomFactor;
    double threshold;
    bool forceEndpoints;
    double *zoomLevelBreaks;
    
    void _buildZoomLevelBreaks();
    double distance(const std::pair<double,double>& p0, const std::pair<double,double>& p1, const std::pair<double,double>& p2) const;
    inline int floor1e5(double coordinate) const { return static_cast<int> (floor(coordinate * 1e5)); }
    std::string encodeSignedNumber(int num) const;
    std::string encodeNumber(int num) const;
    int computeLevel(const double absMaxDist) const;
    std::auto_ptr<std::pair<std::string, std::string> > encode(std::vector<std::pair<double,double> >& points, const double dists[], double absMaxDist);
 
    // if we want to allow copying we need to implement these so we copy zoomLevelBreaks
    GPolyEncoder(const GPolyEncoder &rhs);
    GPolyEncoder & operator = (const GPolyEncoder &rhs);
public:
    explicit GPolyEncoder(int numLevels=18, int zoomFactor=2, double threshold=0.00001, bool forceEndpoints=true);
    ~GPolyEncoder();

    std::auto_ptr<std::pair<std::string, std::string> > dpEncode(std::vector<std::pair<double, double> >& points);
    int getNumLevels() { return numLevels; }
    int getZoomFactor() { return zoomFactor; }
};

#endif /*GPOLYENCODER_H_*/
