#ifndef _LOGISTICREGRESSIONSCORETEST_H_
#define _LOGISTICREGRESSIONSCORETEST_H_

// #include "MathCholesky.h"
// #include "StringHash.h"
// #include "StringArray.h"
#include <cmath>
// #include "MathStats.h"
// #include "MathSVD.h"

#include "base/MathMatrix.h"
#include "regression/LogisticRegression.h"

class LogisticRegressionScoreTest {
 public:
  LogisticRegressionScoreTest();

  /**
   * @param colToTest: 0-based
   */
  bool FitLogisticModel(Matrix& X, Vector& y, int colToTest, int nRound);

  bool FitNullModel(Matrix& Xnull, Vector& y, int nRound);
  bool TestCovariate(Matrix& Xnull, Vector& y, Vector& Xcol);

  /**
   * Test H0: \beta = 0  (\beta is multiple dimension).
   * y ~ \beta * Xcol + \gamma * Xnull
   */
  bool TestCovariate(const Matrix& Xnull, const Vector& y, const Matrix& Xcol);

  // fit y~1+ beta*x  (no covariate)
  bool TestCovariate(Vector& x, Vector& y);
  /**
   * Test y~ 1 + \beta * X (no covariate)
   */
  bool TestCovariate(Matrix& x, Vector& y);

  double GetPvalue() const { return this->pvalue; };
  double GetStat() const { return this->stat; };
  const Matrix& GetU() const { return this->Umatrix; };
  const Matrix& GetV() const { return this->Vmatrix; };
  Vector& GetNullPredicted() {
    return this->lr.GetPredicted();
  };  // predicted probability \hat{p}

  // get estimates from null model
  Vector& GetNullCovEst() {
    return this->lr.GetCovEst();
  };  // coef estimation of the model
  Matrix& GetNullCovB() { return this->lr.GetCovB(); };

 private:
  void splitMatrix(const Matrix& x, int col, Matrix& xnull, Vector& xcol);
  double stat;
  double pvalue;
  Matrix Umatrix;
  Matrix Vmatrix;
  LogisticRegression lr;
};

#endif /* _LOGISTICREGRESSIONSCORETEST_H_ */
