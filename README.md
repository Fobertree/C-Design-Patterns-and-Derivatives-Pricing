# C-Design-Patterns-and-Derivatives-Pricing

> [!NOTE]
> Based on the textbook of the same name

## General Notes

### Markov Chains/Markov process

Predicting future states based on current state

- Higher order Markov chains sort of represent a sliding window of values from previous timesteps to predict future state

### Ito's Lemma

Very similar to Taylor Series.

$df(X_t) = f^{'} (X_t)dX_t + \frac{1}{2}f^{"} (X_t) d[X]_t$
