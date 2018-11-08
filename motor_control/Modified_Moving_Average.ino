#ifndef MMA
#define MMA

class Mma {
  private:
      unsigned int averageCount;
      float movingAverage;
      float movingAverageSum;
      float (*valueGetter)();
  public:
    Mma(unsigned int _averageCount, float (*_valueGetter)()){
        averageCount = _averageCount;
        valueGetter = _valueGetter;
        // Pre-load MMA
        for (int x=0; x < averageCount; x++)
          movingAverageSum = movingAverageSum + (*valueGetter)();
           
         // Calculate inital average
         movingAverage = movingAverageSum / averageCount;
    }
    // This will sample the fn given and update the mma
    void sample() {
      float currentValue = (*valueGetter)();
      // Remove previous movingAverage from the sum
      movingAverageSum = movingAverageSum - movingAverage;
      // Replace it with the current sample
      movingAverageSum = movingAverageSum + currentValue;
      // Recalculate movingAverage
      movingAverage = movingAverageSum / averageCount;
    }
    // This will return the current average
    float getAverage() {
        return movingAverage;
    }
};
#endif
