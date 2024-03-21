# Monte Carlo & Black Scholes Options Pricing

[//]: #https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax

**General stock price movement**
$dS_t = \mu S_t dt + \sigma S_t dW_t$

- $\mu$ is the drift coefficient (stock returns)

**Black Scholes**\
Riskless bond $B$ growing at continuously compounding rate $r$. Given a vanilla option with expiry $T$ and pay-off $f$, is equal to:\
$e^{-rT} E(f(S_T))$ (2)

- We are discounting the strike price to present value ($e^{-rT}$) while $f(S_T)$ is the underlying asset at expiration (reminder Black Scholes is based on European options, can only exercise at expiration)

**Risk-neutral process (SDE but at lowest return we'll take)**
$dS_t = rS_t dt + \sigma S_t dW_t $

**Pass into log and use Ito's lemma**

> [!WARNING]
> Ito's Lemma is something I need to understand better.

- $dlog S_t = (r-\frac{1}{2}\sigma^2)dt + \sigma dW_t$

$log S_t = (r-\frac{1}{2}\sigma^2)t + \sigma W_t$

Since $W_t$ is a Brownian motion, $W_T$ is a Gaussian distrubtion, with mean $0$ and variance $T$

- $W_T = \sqrt{T} N(0,1)$

Plug it back into $W_T$

$log S_t = log S_0 + (r-\frac{1}{2}\sigma^2)t + \sigma \sqrt{T} N(0,1)$

Take exponential of both sides ($e$)

$S_t = S_0 e^{(r-\frac{1}{2}\sigma^2)t + \sigma \sqrt{T} N(0,1)}$

Plug back into equation 2

**The price of a vanilla option equals**\
$e^{-rT} E(f(S_0 e^{(r-\frac{1}{2}\sigma^2)t + \sigma \sqrt{T} N(0,1)}))$

The equation above sets up our Monte Carlo Simulation.

## Monte Carlo

Monte Carlo approximates this expected value by relying the Law of Large Numbers (a lot of trials $\rightarrow$ individual probability of an event)

### Process

- Draw upon random variable x from $N(0,1)$ gaussian distribution using Box-Muller transform
- Use the x to compute $f(S_0 e^{(r-\frac{1}{2}\sigma^2)t + \sigma \sqrt{T} x})$ (plug into the distribution)\
  - Where $f(S) = (S-K)_+$
    - $(+$ subscript means $max(S-K,0))$
- Repeat many times then take the average
- Multiply the average by $e^{-rT}$ (discount to P.V.)
