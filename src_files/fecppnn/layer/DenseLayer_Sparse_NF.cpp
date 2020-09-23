//
// Created by finne on 9/22/2020.
//

#include "DenseLayer_Sparse_NF.h"

#include <memory.h>

void fecppnn::DenseLayer_Sparse_NF::compute() {

    if (changedSinceLastComputation) {
        skippedComputations++;
    }
    changedSinceLastComputation = false;

    if (skippedComputations == NON_FULLY_UPDATED_RUNS) {
        skippedComputations = 0;

        memset(intermediateOutput->getValues(), 0, sizeof(float) * getOutput()->getSize());

        for (int i = 0; i < inputTracker.count(); i++) {
            adjustInput(inputTracker.at(i), input->get(inputTracker.at(i)));
        }
    }
    
    for(int i = 0; i < getOutput()->getSize(); i+= 8){
        __m256 b = _mm256_load_ps(&bias->getValues()[i]);
        __m256 pre = _mm256_load_ps(&intermediateOutput->getValues()[i]);
        _mm256_store_ps(&getOutput()->getValues()[i], _mm256_add_ps(b, pre));
    }
    
}
void              fecppnn::DenseLayer_Sparse_NF::backprop() {}
const std::string fecppnn::DenseLayer_Sparse_NF::name() { return "DenseLayer_Sparse_NF"; }
void              fecppnn::DenseLayer_Sparse_NF::adjustInput(int index, float val) {
    
    
    if (val == input->get(index)) {
        return;
    }

    if (val == 0) {
        inputTracker.remove(index);
    } else {
        inputTracker.put(index);
    }
    
    changedSinceLastComputation = true;

    float difference = val - input->get(index);
    input->get(index) = val;
    
    __m256 dif = _mm256_set1_ps(difference);

    for (int o = 0; o < getOutput()->getSize(); o += 8) {
        
        __m256 mat0 = _mm256_load_ps(&weights->getValues()[o + getOutput()->getSize() * index]);
        __m256 out  = _mm256_load_ps(&intermediateOutput->getValues()[o]);

        __m256 difForOut = _mm256_mul_ps(mat0, dif);

        out = _mm256_add_ps(difForOut, out);

        _mm256_store_ps(&intermediateOutput->getValues()[o], out);
    }
}
 fecppnn::InputTracker& fecppnn::DenseLayer_Sparse_NF::getInputTracker()  { return inputTracker; }
fecppnn::Data*               fecppnn::DenseLayer_Sparse_NF::getInput() const { return input; }
int  fecppnn::DenseLayer_Sparse_NF::getSkippedComputations() const { return skippedComputations; }
bool fecppnn::DenseLayer_Sparse_NF::isChangedSinceLastComputation() const { return changedSinceLastComputation; }