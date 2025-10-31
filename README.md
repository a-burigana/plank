# The Epistemic Planning Domain Definition Language


## Known Bugs and Limitations

- [ ] When setting the initial conditions of a *problem*, if the requirement `:finitary-S5-theories` is enabled, the modality `Kw.` does **not** work correctly with the modality index `All`, even though it should.

  **Workaround:** Use `:forall` and apply `Kw.` to each individual agent instead.

  **Example (not working):**
  ```lisp
  ([C. All]
   (<Kw. All> (tails)))
  ```

  **Workaround example:**
  ```lisp
  (:forall (?i - agent)
    ([C. All]
      (<Kw. ?i> (tails))))
  ```

- [ ] REMOVE ALL `always`
